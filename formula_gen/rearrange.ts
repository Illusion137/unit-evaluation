/**
 * rearrange.ts
 *
 * Rearranges a LaTeX equation for every variable it contains,
 * expressing each variable as a function of the others.
 *
 * Supports:
 *  - Arithmetic: +, -, *, /, ^  (including \cdot, \times, \div, \frac{}{})
 *  - Grouping: parentheses, \left \right
 *  - Named functions: \sqrt{}, \sqrt[n]{}, \ln, \log, \log_{b}, \sin, \cos,
 *                     \tan, \arcsin, \arccos, \arctan, \exp, \abs
 *  - Greek letters as variable names (e.g. \alpha, \beta, \omega, …)
 *  - Modifier prefixes: \delta x, \Delta x, \partial x  → single variable
 *  - Font/accent commands: \mathcal{X}, \mathbf{v}, \hat{x}, \vec{x}, etc.
 *  - Subscript variables (e.g. v_0, x_1)
 *  - Implicit multiplication (adjacent terms)
 *
 * Dependencies: none (pure TypeScript, no external packages required)
 */

// ─────────────────────────────────────────────────────────────────────────────
// AST Node Types
// ─────────────────────────────────────────────────────────────────────────────

type NodeKind =
  | "num"       // numeric literal
  | "var"       // variable (leaf)
  | "add"       // a + b
  | "sub"       // a - b
  | "mul"       // a * b
  | "div"       // a / b
  | "pow"       // a ^ b
  | "neg"       // unary minus
  | "fn"        // named function: fn(arg) or fn(arg, arg2)
  | "eq";       // equation: lhs = rhs  (top-level only)

interface Num { kind: "num"; value: number }
interface Var { kind: "var"; name: string }
interface BinOp { kind: "add" | "sub" | "mul" | "div" | "pow"; left: Node; right: Node }
interface Neg { kind: "neg"; arg: Node }
interface Fn { kind: "fn"; name: string; args: Node[] }
interface Eq { kind: "eq"; left: Node; right: Node }

type Node = Num | Var | BinOp | Neg | Fn | Eq;

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────

const num = (value: number): Num => ({ kind: "num", value });
const var_ = (name: string): Var => ({ kind: "var", name });
const add = (l: Node, r: Node): BinOp => ({ kind: "add", left: l, right: r });
const sub = (l: Node, r: Node): BinOp => ({ kind: "sub", left: l, right: r });
const mul = (l: Node, r: Node): BinOp => ({ kind: "mul", left: l, right: r });
const div = (l: Node, r: Node): BinOp => ({ kind: "div", left: l, right: r });
const pow = (l: Node, r: Node): BinOp => ({ kind: "pow", left: l, right: r });
const neg = (a: Node): Neg => ({ kind: "neg", arg: a });
const fn_ = (name: string, ...args: Node[]): Fn => ({ kind: "fn", name, args });
const eq_ = (l: Node, r: Node): Eq => ({ kind: "eq", left: l, right: r });

function is_num(n: Node): n is Num { return n.kind === "num"; }
function is_var(n: Node): n is Var { return n.kind === "var"; }

// ─────────────────────────────────────────────────────────────────────────────
// Tokeniser
// ─────────────────────────────────────────────────────────────────────────────

const GREEK = [
  "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta",
  "iota", "kappa", "lambda", "mu", "nu", "xi", "pi", "rho", "sigma", "tau",
  "upsilon", "phi", "chi", "psi", "omega",
  "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Theta",
  "Iota", "Kappa", "Lambda", "Mu", "Nu", "Xi", "Pi", "Rho", "Sigma", "Tau",
  "Upsilon", "Phi", "Chi", "Psi", "Omega",
];

// Named LaTeX commands that are variables/constants rather than functions
const VARIABLE_COMMANDS = new Set([...GREEK, "infty", "infinity", "partial"]);

// Commands that act as "modifier prefixes" — they combine with the NEXT token
// to form a single compound variable name, e.g. \delta x → "\delta x"
// \partial is also in VARIABLE_COMMANDS so it can stand alone; we handle the
// "followed by letter/command" case specially in the parser.
const MODIFIER_PREFIXES = new Set([
  "delta", "Delta", "partial",
  "nabla",   // ∇ — often used as operator prefix
]);

// Font / accent commands whose brace argument becomes the variable body.
// e.g. \mathcal{L} → variable named "\mathcal{L}"
//      \hat{x}     → variable named "\hat{x}"
//      \vec{v}     → variable named "\vec{v}"
const FONT_ACCENT_COMMANDS = new Set([
  // Math font commands
  "mathcal", "mathbb", "mathbf", "mathit", "mathrm", "mathsf", "mathtt", "mathfrak",
  "boldsymbol", "bm", "pmb",
  // Accent / decoration commands
  "hat", "tilde", "bar", "vec", "dot", "ddot", "breve", "check", "acute", "grave",
  "widehat", "widetilde", "overline", "underline", "overrightarrow", "overleftarrow",
  "overbrace", "underbrace",
]);

// Named functions we handle symbolically
const KNOWN_FN = new Set([
  "sin", "cos", "tan", "sec", "csc", "cot",
  "arcsin", "arccos", "arctan",
  "sinh", "cosh", "tanh",
  "ln", "log", "exp", "sqrt", "abs", "sgn",
]);

type TokenKind =
  | "num" | "ident" | "latex_cmd" | "op" | "lparen" | "rparen"
  | "lbrace" | "rbrace" | "lbracket" | "rbracket"
  | "eq" | "hat" | "underscore" | "comma" | "eof";

interface Token { kind: TokenKind; value: string }

function tokenise(latex: string): Token[] {
  // Normalise whitespace and strip display-math wrappers
  let s = latex.trim()
    .replace(/^\s*\$\$?\s*/, "").replace(/\s*\$?\$\s*$/, "")
    .replace(/\\left\s*/g, "").replace(/\\right\s*/g, "")
    .replace(/\\!/g, "").replace(/\\,/g, "").replace(/\\;/g, "")
    .replace(/\\quad/g, "").replace(/\\qquad/g, "")
    .replace(/\s+/g, " ");

  const tokens: Token[] = [];
  let i = 0;

  while (i < s.length) {
    const ch = s[i];

    // Whitespace
    if (ch === " ") { i++; continue; }

    // Numbers (including decimals)
    if (/\d/.test(ch) || (ch === "." && /\d/.test(s[i + 1] ?? ""))) {
      let num = "";
      while (i < s.length && /[\d.]/.test(s[i])) num += s[i++];
      tokens.push({ kind: "num", value: num });
      continue;
    }

    // Latin letter identifier
    if (/[a-zA-Z]/.test(ch)) {
      tokens.push({ kind: "ident", value: ch });
      i++;
      continue;
    }

    // LaTeX commands
    if (ch === "\\") {
      i++; // consume backslash
      let cmd = "";
      if (i < s.length && /[a-zA-Z]/.test(s[i])) {
        while (i < s.length && /[a-zA-Z]/.test(s[i])) cmd += s[i++];
      } else if (i < s.length) {
        cmd = s[i++];
      }
      // Map operator aliases
      if (cmd === "cdot" || cmd === "times") {
        tokens.push({ kind: "op", value: "*" });
      } else if (cmd === "div") {
        tokens.push({ kind: "op", value: "/" });
      } else if (cmd === "pm") {
        tokens.push({ kind: "op", value: "+" }); // approximate ±
      } else if (cmd === "frac") {
        tokens.push({ kind: "latex_cmd", value: "frac" });
      } else if (cmd === "sqrt") {
        tokens.push({ kind: "latex_cmd", value: "sqrt" });
      } else {
        tokens.push({ kind: "latex_cmd", value: cmd });
      }
      continue;
    }

    // Single-char operators and punctuation
    switch (ch) {
      case "+": tokens.push({ kind: "op", value: "+" }); break;
      case "-": tokens.push({ kind: "op", value: "-" }); break;
      case "*": tokens.push({ kind: "op", value: "*" }); break;
      case "/": tokens.push({ kind: "op", value: "/" }); break;
      case "^": tokens.push({ kind: "hat", value: "^" }); break;
      case "_": tokens.push({ kind: "underscore", value: "_" }); break;
      case "=": tokens.push({ kind: "eq", value: "=" }); break;
      case "(": tokens.push({ kind: "lparen", value: "(" }); break;
      case ")": tokens.push({ kind: "rparen", value: ")" }); break;
      case "{": tokens.push({ kind: "lbrace", value: "{" }); break;
      case "}": tokens.push({ kind: "rbrace", value: "}" }); break;
      case "[": tokens.push({ kind: "lbracket", value: "[" }); break;
      case "]": tokens.push({ kind: "rbracket", value: "]" }); break;
      case ",": tokens.push({ kind: "comma", value: "," }); break;
      default: /* ignore */ break;
    }
    i++;
  }

  tokens.push({ kind: "eof", value: "" });
  return tokens;
}

// ─────────────────────────────────────────────────────────────────────────────
// Parser  (recursive descent, Pratt-style precedence)
// ─────────────────────────────────────────────────────────────────────────────

class Parser {
  private tokens: Token[];
  private pos = 0;

  constructor(tokens: Token[]) { this.tokens = tokens; }

  private peek(): Token { return this.tokens[this.pos]; }
  private consume(): Token { return this.tokens[this.pos++]; }
  private expect(kind: TokenKind, value?: string): Token {
    const t = this.consume();
    if (t.kind !== kind || (value !== undefined && t.value !== value))
      throw new Error(`Expected ${kind}${value ? `(${value})` : ""}, got ${t.kind}(${t.value})`);
    return t;
  }

  // ── Entry point ────────────────────────────────────────────────────────────
  parseEquation(): Node {
    const lhs = this.parseExpr();
    if (this.peek().kind === "eq") {
      this.consume();
      const rhs = this.parseExpr();
      return eq_(lhs, rhs);
    }
    return eq_(lhs, num(0));
  }

  // expression = term ((+ | -) term)*
  parseExpr(): Node {
    let left = this.parseTerm();
    while (true) {
      const t = this.peek();
      if (t.kind === "op" && t.value === "+") {
        this.consume(); left = add(left, this.parseTerm());
      } else if (t.kind === "op" && t.value === "-") {
        this.consume(); left = sub(left, this.parseTerm());
      } else {
        break;
      }
    }
    return left;
  }

  // term = unary (('*' | '/') unary | implicit-mul)*
  parseTerm(): Node {
    let left = this.parseUnary();
    while (true) {
      const t = this.peek();
      if (t.kind === "op" && t.value === "*") {
        this.consume(); left = mul(left, this.parseUnary());
      } else if (t.kind === "op" && t.value === "/") {
        this.consume(); left = div(left, this.parseUnary());
      } else if (t.kind === "latex_cmd" && t.value === "frac") {
        this.consume();
        const numerator = this.parseBraceGroup();
        const denominator = this.parseBraceGroup();
        left = mul(left, div(numerator, denominator));
      } else if (this.isImplicitMulStart()) {
        left = mul(left, this.parseUnary());
      } else {
        break;
      }
    }
    return left;
  }

  private isImplicitMulStart(): boolean {
    const t = this.peek();
    return (
      t.kind === "num" ||
      t.kind === "ident" ||
      t.kind === "lparen" ||
      t.kind === "lbrace" ||
      (t.kind === "latex_cmd" && (
        VARIABLE_COMMANDS.has(t.value) ||
        MODIFIER_PREFIXES.has(t.value) ||
        FONT_ACCENT_COMMANDS.has(t.value) ||
        KNOWN_FN.has(t.value) ||
        t.value === "frac" ||
        t.value === "sqrt"
      ))
    );
  }

  // unary = '-' unary | power
  parseUnary(): Node {
    if (this.peek().kind === "op" && this.peek().value === "-") {
      this.consume();
      return neg(this.parseUnary());
    }
    return this.parsePower();
  }

  // power = atom ('^' braceOrAtom)*   (right-associative)
  parsePower(): Node {
    let base = this.parseAtom();
    if (this.peek().kind === "hat") {
      this.consume();
      const exp = this.parseBraceOrAtom();
      base = pow(base, exp);
    }
    return base;
  }

  // atom = num | ident[_subscript] | latex_cmd(…) | '(' expr ')' | '{' expr '}'
  parseAtom(): Node {
    const t = this.peek();

    // Number
    if (t.kind === "num") {
      this.consume();
      return num(parseFloat(t.value));
    }

    // Single latin letter — may have subscript
    if (t.kind === "ident") {
      this.consume();
      let name = t.value;
      if (this.peek().kind === "underscore") {
        this.consume();
        const sub = this.parseBraceOrAtom();
        name += "_" + nodeToLatex(sub);
      }
      return var_(name);
    }

    // LaTeX command
    if (t.kind === "latex_cmd") {
      this.consume();
      return this.parseCommand(t.value);
    }

    // Parenthesised expression
    if (t.kind === "lparen") {
      this.consume();
      const inner = this.parseExpr();
      if (this.peek().kind === "rparen") this.consume();
      return inner;
    }

    // Brace-grouped expression
    if (t.kind === "lbrace") {
      return this.parseBraceGroup();
    }

    throw new Error(`Unexpected token: ${t.kind}(${t.value})`);
  }

  private parseCommand(cmd: string): Node {

    // ── Font / accent commands: \mathcal{X}, \hat{x}, \vec{v}, etc.
    // These wrap their argument and the whole thing is ONE variable.
    if (FONT_ACCENT_COMMANDS.has(cmd)) {
      // Argument must be in braces (or a single ident/cmd after the command)
      const argNode = this.parseBraceOrAtom();
      // Build a variable name like "\mathcal{L}" or "\hat{x}"
      let baseName = nodeVarName(argNode) ?? nodeToLatex(argNode);
      let name = `\\${cmd}{${baseName}}`;
      // Allow subscript after the whole thing: \mathcal{H}_k
      if (this.peek().kind === "underscore") {
        this.consume();
        const sub = this.parseBraceOrAtom();
        name += "_" + nodeToLatex(sub);
      }
      return var_(name);
    }

    // ── Modifier prefixes: \delta x, \Delta t, \partial x
    // The prefix fuses with the immediately following symbol to form one variable.
    if (MODIFIER_PREFIXES.has(cmd)) {
      const next = this.peek();
      // If the next token is a letter or known command, absorb it
      if (next.kind === "ident" || next.kind === "latex_cmd") {
        this.consume(); // consume the next token
        let suffix: string;
        if (next.kind === "ident") {
          suffix = next.value;
        } else {
          // It's a latex_cmd — could itself be a font/accent or greek
          suffix = `\\${next.value}`;
        }
        let name = `\\${cmd} ${suffix}`;
        // Allow subscript: \delta x_0
        if (this.peek().kind === "underscore") {
          this.consume();
          const sub = this.parseBraceOrAtom();
          name += "_" + nodeToLatex(sub);
        }
        return var_(name);
      }
      // No following letter → treat as standalone variable (e.g. bare \partial)
      let name = `\\${cmd}`;
      if (this.peek().kind === "underscore") {
        this.consume();
        const sub = this.parseBraceOrAtom();
        name += "_" + nodeToLatex(sub);
      }
      return var_(name);
    }

    // ── Greek letters / constants → variable
    if (VARIABLE_COMMANDS.has(cmd)) {
      let name = `\\${cmd}`;
      if (this.peek().kind === "underscore") {
        this.consume();
        const sub = this.parseBraceOrAtom();
        name += "_" + nodeToLatex(sub);
      }
      return var_(name);
    }

    // ── \sqrt[n]{x}  or  \sqrt{x}
    if (cmd === "sqrt") {
      let n: Node = num(2);
      if (this.peek().kind === "lbracket") {
        this.consume();
        n = this.parseExpr();
        this.expect("rbracket");
      }
      const arg = this.parseBraceGroup();
      return pow(arg, div(num(1), n));
    }

    // ── \frac{num}{denom}
    if (cmd === "frac") {
      const numerator = this.parseBraceGroup();
      const denominator = this.parseBraceGroup();
      return div(numerator, denominator);
    }

    // ── \log_{base}{arg}  or  \log{arg}
    if (cmd === "log") {
      let base: Node = num(10);
      if (this.peek().kind === "underscore") {
        this.consume();
        base = this.parseBraceOrAtom();
      }
      const arg = this.parseBraceOrAtom();
      return fn_("log", arg, base);
    }

    // ── Known trig / analytic functions
    if (KNOWN_FN.has(cmd)) {
      const arg = this.parseBraceOrAtom();
      return fn_(cmd, arg);
    }

    // ── Unknown command — treat as variable
    let name = `\\${cmd}`;
    if (this.peek().kind === "underscore") {
      this.consume();
      const sub = this.parseBraceOrAtom();
      name += "_" + nodeToLatex(sub);
    }
    return var_(name);
  }

  // Parse { expr }
  private parseBraceGroup(): Node {
    this.expect("lbrace");
    const inner = this.parseExpr();
    if (this.peek().kind === "rbrace") this.consume();
    return inner;
  }

  // Parse either a brace group or a single atom
  private parseBraceOrAtom(): Node {
    if (this.peek().kind === "lbrace") return this.parseBraceGroup();
    return this.parseAtom();
  }
}

// Helper: if a node is a plain variable, return its name; else null.
function nodeVarName(n: Node): string | null {
  return n.kind === "var" ? n.name : null;
}

// ─────────────────────────────────────────────────────────────────────────────
// Variable extraction
// ─────────────────────────────────────────────────────────────────────────────

function collectVars(node: Node, out = new Set<string>()): Set<string> {
  switch (node.kind) {
    case "var": out.add(node.name); break;
    case "num": break;
    case "neg": collectVars(node.arg, out); break;
    case "fn": node.args.forEach(a => collectVars(a, out)); break;
    case "eq":
    case "add": case "sub": case "mul": case "div": case "pow":
      collectVars(node.left, out);
      collectVars(node.right, out);
      break;
  }
  return out;
}

// ─────────────────────────────────────────────────────────────────────────────
// Simplifier  (constant folding + basic algebraic identities)
// ─────────────────────────────────────────────────────────────────────────────

function simplify(n: Node): Node {
  switch (n.kind) {
    case "num":
    case "var":
      return n;
    case "neg": {
      const a = simplify(n.arg);
      if (is_num(a)) return num(-a.value);
      if (a.kind === "neg") return a.arg;
      return neg(a);
    }
    case "add": {
      const l = simplify(n.left), r = simplify(n.right);
      if (is_num(l) && is_num(r)) return num(l.value + r.value);
      if (is_num(l) && l.value === 0) return r;
      if (is_num(r) && r.value === 0) return l;
      return add(l, r);
    }
    case "sub": {
      const l = simplify(n.left), r = simplify(n.right);
      if (is_num(l) && is_num(r)) return num(l.value - r.value);
      if (is_num(r) && r.value === 0) return l;
      if (is_num(l) && l.value === 0) return neg(r);
      if (nodeToLatex(l) === nodeToLatex(r)) return num(0);
      return sub(l, r);
    }
    case "mul": {
      const l = simplify(n.left), r = simplify(n.right);
      if (is_num(l) && is_num(r)) return num(l.value * r.value);
      if (is_num(l) && l.value === 0) return num(0);
      if (is_num(r) && r.value === 0) return num(0);
      if (is_num(l) && l.value === 1) return r;
      if (is_num(r) && r.value === 1) return l;
      if (is_num(l) && l.value === -1) return neg(r);
      if (is_num(r) && r.value === -1) return neg(l);
      return mul(l, r);
    }
    case "div": {
      const l = simplify(n.left), r = simplify(n.right);
      if (is_num(l) && is_num(r) && r.value !== 0) return num(l.value / r.value);
      if (is_num(l) && l.value === 0) return num(0);
      if (is_num(r) && r.value === 1) return l;
      if (nodeToLatex(l) === nodeToLatex(r)) return num(1);
      return div(l, r);
    }
    case "pow": {
      const l = simplify(n.left), r = simplify(n.right);
      if (is_num(l) && is_num(r)) return num(Math.pow(l.value, r.value));
      if (is_num(r) && r.value === 1) return l;
      if (is_num(r) && r.value === 0) return num(1);
      if (is_num(l) && l.value === 1) return num(1);
      return pow(l, r);
    }
    case "fn": {
      const args = n.args.map(simplify);
      if (args.length === 1 && is_num(args[0])) {
        const v = args[0].value;
        const fns: Record<string, (x: number) => number> = {
          sin: Math.sin, cos: Math.cos, tan: Math.tan,
          arcsin: Math.asin, arccos: Math.acos, arctan: Math.atan,
          sinh: Math.sinh, cosh: Math.cosh, tanh: Math.tanh,
          ln: Math.log, exp: Math.exp, abs: Math.abs, sqrt: Math.sqrt,
        };
        if (n.name in fns) return num(fns[n.name](v));
      }
      return { ...n, args };
    }
    case "eq":
      return eq_(simplify(n.left), simplify(n.right));
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// containsVar
// ─────────────────────────────────────────────────────────────────────────────

function containsVar(node: Node, varName: string): boolean {
  switch (node.kind) {
    case "var": return node.name === varName;
    case "num": return false;
    case "neg": return containsVar(node.arg, varName);
    case "fn": return node.args.some(a => containsVar(a, varName));
    case "eq": case "add": case "sub": case "mul": case "div": case "pow":
      return containsVar(node.left, varName) || containsVar(node.right, varName);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// Algebraic solver: isolate `target` variable on the LHS
// ─────────────────────────────────────────────────────────────────────────────

function isolate(lhs: Node, rhs: Node, target: string): Node | null {
  lhs = simplify(lhs);
  rhs = simplify(rhs);

  if (is_var(lhs) && lhs.name === target) return simplify(rhs);
  if (is_num(lhs)) return null;
  if (is_var(lhs)) return null;

  switch (lhs.kind) {
    case "neg":
      return isolate(lhs.arg, neg(rhs), target);

    case "add": {
      if (containsVar(lhs.left, target))
        return isolate(lhs.left, sub(rhs, lhs.right), target);
      if (containsVar(lhs.right, target))
        return isolate(lhs.right, sub(rhs, lhs.left), target);
      return null;
    }
    case "sub": {
      if (containsVar(lhs.left, target))
        return isolate(lhs.left, add(rhs, lhs.right), target);
      if (containsVar(lhs.right, target))
        return isolate(lhs.right, sub(lhs.left, rhs), target);
      return null;
    }
    case "mul": {
      if (containsVar(lhs.left, target))
        return isolate(lhs.left, div(rhs, lhs.right), target);
      if (containsVar(lhs.right, target))
        return isolate(lhs.right, div(rhs, lhs.left), target);
      return null;
    }
    case "div": {
      if (containsVar(lhs.left, target))
        return isolate(lhs.left, mul(rhs, lhs.right), target);
      if (containsVar(lhs.right, target))
        return isolate(lhs.right, div(lhs.left, rhs), target);
      return null;
    }
    case "pow": {
      if (containsVar(lhs.left, target))
        return isolate(lhs.left, pow(rhs, div(num(1), lhs.right)), target);
      if (containsVar(lhs.right, target))
        return isolate(lhs.right, div(fn_("ln", rhs), fn_("ln", lhs.left)), target);
      return null;
    }
    case "fn": {
      const arg0 = lhs.args[0];
      if (!arg0 || !containsVar(arg0, target)) return null;

      const inverses: Record<string, (r: Node, args: Node[]) => Node> = {
        ln: (r) => fn_("exp", r),
        exp: (r) => fn_("ln", r),
        sin: (r) => fn_("arcsin", r),
        cos: (r) => fn_("arccos", r),
        tan: (r) => fn_("arctan", r),
        arcsin: (r) => fn_("sin", r),
        arccos: (r) => fn_("cos", r),
        arctan: (r) => fn_("tan", r),
        sinh: (r) => fn_("arcsinh", r),
        cosh: (r) => fn_("arccosh", r),
        tanh: (r) => fn_("arctanh", r),
        abs: (r) => r,
        log: (r, args) => pow(args[1] ?? num(10), r),
      };

      if (lhs.name in inverses) {
        const inv = inverses[lhs.name](rhs, lhs.args);
        return isolate(arg0, inv, target);
      }
      if (lhs.name === "sqrt") {
        return isolate(arg0, pow(rhs, num(2)), target);
      }
      return null;
    }
  }
  return null;
}

// ─────────────────────────────────────────────────────────────────────────────
// LaTeX serialiser
// ─────────────────────────────────────────────────────────────────────────────

function needsParens(node: Node, parentKind: NodeKind): boolean {
  if (node.kind === "add" || node.kind === "sub")
    return parentKind === "mul" || parentKind === "div" || parentKind === "pow" || parentKind === "neg";
  if (node.kind === "neg")
    return parentKind === "pow";
  return false;
}

function wrap(node: Node, parentKind: NodeKind): string {
  const s = nodeToLatex(node);
  return needsParens(node, parentKind) ? `\\left(${s}\\right)` : s;
}

function nodeToLatex(node: Node): string {
  switch (node.kind) {
    case "num": {
      const v = node.value;
      if (Number.isFinite(v) && !Number.isInteger(v)) {
        for (const d of [2, 3, 4, 5, 6, 7, 8, 9, 10, 12]) {
          const n = Math.round(v * d);
          if (Math.abs(n / d - v) < 1e-10) {
            if (n < 0) return `-\\frac{${-n}}{${d}}`;
            return `\\frac{${n}}{${d}}`;
          }
        }
      }
      return String(v);
    }
    case "var":
      return node.name;
    case "neg":
      return `-${wrap(node.arg, "neg")}`;
    case "add":
      return `${nodeToLatex(node.left)} + ${nodeToLatex(node.right)}`;
    case "sub": {
      const r = node.right;
      const rStr = (r.kind === "add" || r.kind === "sub")
        ? `\\left(${nodeToLatex(r)}\\right)`
        : nodeToLatex(r);
      return `${nodeToLatex(node.left)} - ${rStr}`;
    }
    case "mul": {
      const l = wrap(node.left, "mul");
      const r = wrap(node.right, "mul");
      const rNode = node.right;
      const lNode = node.left;
      const rIsAlpha = rNode.kind === "var" || rNode.kind === "fn" ||
        (rNode.kind === "pow" && (rNode.left.kind === "var" || rNode.left.kind === "fn"));
      const lIsNum = lNode.kind === "num";
      if (lIsNum && rIsAlpha) return `${l} ${r}`;
      return `${l} \\cdot ${r}`;
    }
    case "div":
      return `\\frac{${nodeToLatex(node.left)}}{${nodeToLatex(node.right)}}`;
    case "pow": {
      const base = node.left;
      const bStr = (base.kind === "var" || base.kind === "num")
        ? nodeToLatex(base)
        : `\\left(${nodeToLatex(base)}\\right)`;
      return `${bStr}^{${nodeToLatex(node.right)}}`;
    }
    case "fn": {
      const latexNames: Record<string, string> = {
        arcsin: "\\arcsin", arccos: "\\arccos", arctan: "\\arctan",
        arcsinh: "\\text{arcsinh}", arccosh: "\\text{arccosh}", arctanh: "\\text{arctanh}",
        sin: "\\sin", cos: "\\cos", tan: "\\tan",
        sinh: "\\sinh", cosh: "\\cosh", tanh: "\\tanh",
        ln: "\\ln", exp: "\\exp",
        log: "\\log",
        sqrt: "\\sqrt",
      };
      if (node.name === "abs") {
        return `\\left|${nodeToLatex(node.args[0])}\\right|`;
      }
      if (node.name === "log" && node.args.length === 2) {
        return `\\log_{${nodeToLatex(node.args[1])}} ${nodeToLatex(node.args[0])}`;
      }
      const cmd = latexNames[node.name] ?? `\\${node.name}`;
      if (node.args.length === 1) {
        return `${cmd}\\left(${nodeToLatex(node.args[0])}\\right)`;
      }
      return `${cmd}\\left(${node.args.map(nodeToLatex).join(", ")}\\right)`;
    }
    case "eq":
      return `${nodeToLatex(node.left)} = ${nodeToLatex(node.right)}`;
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// Public API
// ─────────────────────────────────────────────────────────────────────────────

export interface RearrangementResult {
  /** The variable being isolated. */
  variable: string;
  /** The rearranged equation as a LaTeX string. */
  latex: string;
  /** True if the rearrangement was successfully solved. */
  solved: boolean;
  /** Reason if not solved. */
  reason?: string;
}

/**
 * Takes a LaTeX equation (or expression = 0) and returns all rearrangements,
 * one per variable found in the equation.
 */
export function rearrangeLatex(latex: string): RearrangementResult[] {
  let equation: Node;
  try {
    const tokens = tokenise(latex);
    const parser = new Parser(tokens);
    equation = parser.parseEquation();
  } catch (err) {
    return [{ variable: "?", latex, solved: false, reason: `Parse error: ${err}` }];
  }

  const vars = Array.from(collectVars(equation)).sort();

  if (vars.length === 0)
    return [{ variable: "?", latex, solved: false, reason: "No variables found." }];

  const eq = equation as Eq;
  const results: RearrangementResult[] = [];

  for (const v of vars) {
    const combined = sub(eq.left, eq.right);
    let solution: Node | null = null;

    if (containsVar(eq.left, v))
      solution = isolate(eq.left, eq.right, v);

    if (solution === null && containsVar(eq.right, v))
      solution = isolate(eq.right, eq.left, v);

    if (solution === null)
      solution = isolate(simplify(combined), num(0), v);

    if (solution !== null) {
      results.push({ variable: v, latex: `${v} = ${nodeToLatex(simplify(solution))}`, solved: true });
    } else {
      results.push({
        variable: v,
        latex: nodeToLatex(equation),
        solved: false,
        reason: `Could not isolate '${v}' — it may appear in multiple terms or nonlinear position.`,
      });
    }
  }

  return results;
}

// ─────────────────────────────────────────────────────────────────────────────
// CLI demo
// ─────────────────────────────────────────────────────────────────────────────

const DEMO_EQUATIONS = [
  // Original demos
  "v = u + at",
  "E = mc^2",
  "\\frac{1}{2}mv^2 = mgh",
  "PV = nRT",
  "F = \\frac{Gm_1 m_2}{r^2}",
  "v^2 = u^2 + 2as",
  "T = 2\\pi\\sqrt{\\frac{L}{g}}",
  "\\ln(N) = \\ln(N_0) - \\lambda t",
  // New: modifier prefix variables
  "v = v_0 + a \\delta t",
  "\\Delta x = v_0 t + \\frac{1}{2} a t^2",
  "\\partial E = \\mathcal{H} \\delta q",
  // Font/accent variables
  "\\mathcal{L} = \\mathbf{F} \\cdot \\vec{r}",
  "\\hat{p} = m \\hat{v}",
];

function printResults(latex: string): void {
  console.log(`\n${"─".repeat(60)}`);
  console.log(`  Input:  ${latex}`);
  console.log(`${"─".repeat(60)}`);
  for (const r of rearrangeLatex(latex)) {
    if (r.solved) {
      console.log(`  ✓  ${r.latex}`);
    } else {
      console.log(`  ✗  [${r.variable}] ${r.reason}`);
    }
  }
}

// (function runDemo() {
//   console.log("\n╔══════════════════════════════════════════════════════════╗");
//   console.log("║          LaTeX Formula Rearrangement Engine              ║");
//   console.log("╚══════════════════════════════════════════════════════════╝");
//   for (const eq of DEMO_EQUATIONS) printResults(eq);
//   console.log(`\n${"─".repeat(60)}\n`);
// }());