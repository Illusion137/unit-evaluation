#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <cstddef>
#include <expected>
#include <format>
#include <memory>

static std::string describe_token(const dv::Token& token) {
    switch(token.type) {
        case dv::TokenType::TEOF: return "end of expression";
        case dv::TokenType::NUMERIC_LITERAL: return std::format("number '{}'", token.text);
        case dv::TokenType::IDENTIFIER: return std::format("identifier '{}'", token.text);
        case dv::TokenType::FORMULA_QUERY: return "'?'";
        case dv::TokenType::EQUAL: return "'='";
        case dv::TokenType::PLUS: return "'+'";
        case dv::TokenType::MINUS: return "'-'";
        case dv::TokenType::TIMES: return "'*'";
        case dv::TokenType::DIVIDE: return "'/'";
        case dv::TokenType::FRACTION: return "'\\frac'";
        case dv::TokenType::EXPONENT: return "'^'";
        case dv::TokenType::FACTORIAL: return "'!'";
        case dv::TokenType::ABSOLUTE_BAR: return "'|'";
        case dv::TokenType::LEFT_PAREN: return "'('";
        case dv::TokenType::RIGHT_PAREN: return "')'";
        case dv::TokenType::LEFT_CURLY_BRACKET: return "'{'";
        case dv::TokenType::RIGHT_CURLY_BRACKET: return "'}'";
        case dv::TokenType::LEFT_BRACKET: return "'['";
        case dv::TokenType::RIGHT_BRACKET: return "']'";
        case dv::TokenType::LEFT_ABSOLUTE_BAR: return "'\\left|'";
        case dv::TokenType::RIGHT_ABSOLUTE_BAR: return "'\\right|'";
        case dv::TokenType::COMMA: return "','";
        case dv::TokenType::SUBSCRIPT: return "'_'";
        default: {
            if(!token.text.empty()) return std::format("'{}'", token.text);
            return "unknown token";
        }
    }
}

bool dv::Parser::match(dv::TokenType type) {
    if (peek().type == type) { position++; return true; }
    return false;
}

std::int32_t dv::Parser::builtin_function_args(dv::TokenType type){
    switch (type) {
        case dv::TokenType::BUILTIN_FUNC_LN: return 1;
        case dv::TokenType::BUILTIN_FUNC_SIN: return 1;
        case dv::TokenType::BUILTIN_FUNC_COS: return 1;
        case dv::TokenType::BUILTIN_FUNC_TAN: return 1;
        case dv::TokenType::BUILTIN_FUNC_SEC: return 1;
        case dv::TokenType::BUILTIN_FUNC_CSC: return 1;
        case dv::TokenType::BUILTIN_FUNC_COT: return 1;
        case dv::TokenType::BUILTIN_FUNC_LOG: return 1;
        case dv::TokenType::BUILTIN_FUNC_ABS: return 1;
        case dv::TokenType::BUILTIN_FUNC_NCR: return 2;
        case dv::TokenType::BUILTIN_FUNC_NPR: return 2;
        case dv::TokenType::BUILTIN_FUNC_SQRT: return 1;
        case dv::TokenType::BUILTIN_FUNC_CEIL: return 1;
        case dv::TokenType::BUILTIN_FUNC_FACT: return 1;
        case dv::TokenType::BUILTIN_FUNC_FLOOR: return 1;
        case dv::TokenType::BUILTIN_FUNC_ROUND: return 2;
        case dv::TokenType::BUILTIN_FUNC_ARCSIN: return 1;
        case dv::TokenType::BUILTIN_FUNC_ARCCOS: return 1;
        case dv::TokenType::BUILTIN_FUNC_ARCTAN: return 1;
        case dv::TokenType::BUILTIN_FUNC_ARCSEC: return 1;
        case dv::TokenType::BUILTIN_FUNC_ARCCSC: return 1;
        case dv::TokenType::BUILTIN_FUNC_ARCCOT: return 1;
        case dv::TokenType::BUILTIN_FUNC_VALUE: return 1;
        case dv::TokenType::BUILTIN_FUNC_UNIT: return 1;
        default: return 0;
    }
}

std::pair<std::int32_t, std::int32_t> dv::Parser::precedence(dv::TokenType type){
    switch (type) {
        case dv::TokenType::EQUAL:
            return { 1, 1 };
        case dv::TokenType::PLUS:
        case dv::TokenType::MINUS:
            return { 10, 11 };
        case dv::TokenType::TIMES:
        case dv::TokenType::DIVIDE:
            return { 20, 21 };
        case dv::TokenType::FACTORIAL:
            return { 20, 25 };
        case dv::TokenType::EXPONENT:
            return { 31, 30 };
        default: return {-1, -1};
    }
}

bool dv::Parser::is_atom(dv::TokenType type) {
    switch(type) {
        case dv::TokenType::NUMERIC_LITERAL:
        case dv::TokenType::IDENTIFIER:
        case dv::TokenType::ABSOLUTE_BAR:
        case dv::TokenType::FRACTION:
        case dv::TokenType::FORMULA_QUERY:
            return true;
        default: return is_builtin_function(type);
    }
}

bool dv::Parser::is_binop(dv::TokenType type) {
    switch(type) {
        case dv::TokenType::PLUS:
        case dv::TokenType::MINUS:
        case dv::TokenType::TIMES:
        case dv::TokenType::DIVIDE:
        case dv::TokenType::EXPONENT:
        case dv::TokenType::EQUAL:
            return true;
        default: return false;
    }
}

bool dv::Parser::is_builtin_function(dv::TokenType type){
    switch(type){
        case dv::TokenType::BUILTIN_FUNC_LN:
        case dv::TokenType::BUILTIN_FUNC_SIN:
        case dv::TokenType::BUILTIN_FUNC_COS:
        case dv::TokenType::BUILTIN_FUNC_TAN:
        case dv::TokenType::BUILTIN_FUNC_SEC:
        case dv::TokenType::BUILTIN_FUNC_CSC:
        case dv::TokenType::BUILTIN_FUNC_COT:
        case dv::TokenType::BUILTIN_FUNC_LOG:
        case dv::TokenType::BUILTIN_FUNC_ABS:
        case dv::TokenType::BUILTIN_FUNC_NCR:
        case dv::TokenType::BUILTIN_FUNC_NPR:
        case dv::TokenType::BUILTIN_FUNC_SQRT:
        case dv::TokenType::BUILTIN_FUNC_CEIL:
        case dv::TokenType::BUILTIN_FUNC_FACT:
        case dv::TokenType::BUILTIN_FUNC_FLOOR:
        case dv::TokenType::BUILTIN_FUNC_ROUND:
        case dv::TokenType::BUILTIN_FUNC_ARCSIN:
        case dv::TokenType::BUILTIN_FUNC_ARCCOS:
        case dv::TokenType::BUILTIN_FUNC_ARCTAN:
        case dv::TokenType::BUILTIN_FUNC_ARCSEC:
        case dv::TokenType::BUILTIN_FUNC_ARCCSC:
        case dv::TokenType::BUILTIN_FUNC_ARCCOT:
        case dv::TokenType::BUILTIN_FUNC_VALUE:
        case dv::TokenType::BUILTIN_FUNC_UNIT:
            return true;
        default: return false;
    }
}

bool dv::Parser::is_unary_prefix_op(dv::TokenType type){
    switch (type) {
        case dv::TokenType::PLUS:
        case dv::TokenType::MINUS:
            return true;
        default: return false;
    }
}

bool dv::Parser::is_unary_postfix_op(dv::TokenType type){
    switch (type) {
        case dv::TokenType::FACTORIAL:
            return true;
        default: return false;
    }
}

bool dv::Parser::can_implicit_multiply_left(const Token& token) {
    // Prevent implicit multiplication after exponent operations
    if (token.type == TokenType::EXPONENT) return false;
    return is_atom(token.type);
}

dv::MaybeAST dv::Parser::split_single_numeric(){
    if(peek().text[0] == '.') return std::unexpected{"Split numeric can't be '.'"};
    Token base_token = {TokenType::NUMERIC_LITERAL, (double)(peek().text[0] - '0'), peek().text.substr(0, 1)};
    dv::MaybeAST value = std::make_unique<AST>(base_token);
    peek().text = peek().text.substr(1);
    peek().value = std::atof(std::string{peek().text}.c_str());
    return value;
}

dv::MaybeAST dv::Parser::match_square_bracket(){
    if(!match(TokenType::LEFT_BRACKET)){
        return std::unexpected{std::format("Expected '[' but found {}", describe_token(peek()))};
    }
    auto ast = parse_expression(0);
    if(!ast) return ast;
    if(!match(TokenType::RIGHT_BRACKET)){
        return std::unexpected{std::format("Expected ']' but found {}", describe_token(peek()))};
    }
    return ast;
}

dv::MaybeAST dv::Parser::match_curly_bracket(){
    if(!match(TokenType::LEFT_CURLY_BRACKET)){
        return std::unexpected{std::format("Expected '{{' but found {}", describe_token(peek()))};
    }
    auto ast = parse_expression(0);
    if(!ast) return ast;
    if(!match(TokenType::RIGHT_CURLY_BRACKET)){
        return std::unexpected{std::format("Expected '}}' but found {}", describe_token(peek()))};
    }
    return ast;
}

dv::MaybeAST dv::Parser::match_parentheses(){
    if(!match(TokenType::LEFT_PAREN)){
        return std::unexpected{std::format("Expected '(' but found {}", describe_token(peek()))};
    }
    auto ast = parse_expression(0);
    if(!ast) return ast;
    if(!match(TokenType::RIGHT_PAREN)){
        return std::unexpected{std::format("Expected ')' but found {}", describe_token(peek()))};
    }
    return ast;
}

dv::MaybeAST dv::Parser::match_fraction(const dv::Token &token){
    auto numerator = match_curly_bracket();
    if(!numerator) return numerator;
    auto denominator = match_curly_bracket();
    if(!denominator) return denominator;
    return std::make_unique<AST>(token, std::move(numerator.value()), std::move(denominator.value()));
}

dv::MaybeAST dv::Parser::match_exponent(std::int32_t right_binding_power){
    const bool uses_brackets = match(TokenType::LEFT_CURLY_BRACKET);
    MaybeAST rhs = nullptr;
    if(uses_brackets){
        rhs = parse_expression(0);  // Parse full expression in braces
        if(!rhs) return rhs;
        if(!match(TokenType::RIGHT_CURLY_BRACKET)) return std::unexpected{std::format("Expected '}}' after exponent but found {}", describe_token(peek()))};
    }
    else {
        // Without brackets, check if it's a multi-digit number that needs splitting
        if(peek().type == TokenType::NUMERIC_LITERAL && peek().text.size() > 1) {
            rhs = split_single_numeric();
            if(!rhs) return rhs;
        } else {
            // Otherwise, just grab the next LHS term (atom or parenthesized expression)
            // This prevents issues with complex expressions
            rhs = match_lhs(next());
            if(!rhs) return rhs;
        }
    }
    return std::move(rhs.value());
}

dv::MaybeAST dv::Parser::match_absolute_bar(const dv::Token &token){
    auto arg = parse_expression(0);
    if(!arg) return arg;
    if(!match(TokenType::ABSOLUTE_BAR)){
        return std::unexpected{std::format("Expected closing '|' but found {}", describe_token(peek()))};
    }
    std::vector<std::unique_ptr<AST>> args;
    args.emplace_back(std::move(arg.value()));
    // Create an ABS function token
    Token abs_token{TokenType::BUILTIN_FUNC_ABS, "abs"};
    return std::make_unique<AST>(abs_token, std::move(args));
}

dv::MaybeAST dv::Parser::match_sqrt(const dv::Token &token){
    MaybeAST n = nullptr;
    std::vector<std::unique_ptr<AST>> args;
    args.reserve(1);
    if(peek().type == TokenType::LEFT_BRACKET){
        n = match_square_bracket();
        if(!n) return n;
    }
    if(!match(TokenType::LEFT_CURLY_BRACKET)) {
        return std::unexpected{std::format("\\sqrt requires '{{' but found {}", describe_token(peek()))};
    }
    auto arg = parse_expression(0);
    if(!arg) return arg;
    if(!match(TokenType::RIGHT_CURLY_BRACKET)) {
        return std::unexpected{std::format("\\sqrt missing closing '}}', found {}", describe_token(peek()))};
    }
    args.emplace_back(std::move(arg.value()));
    return std::make_unique<AST>(token, std::move(args), std::move(n.value()));
}

dv::MaybeAST dv::Parser::match_log(const dv::Token &token){
    MaybeAST base = nullptr;
    std::vector<std::unique_ptr<AST>> args;
    args.reserve(1);
    if(match(TokenType::SUBSCRIPT)){
        if(match(TokenType::LEFT_CURLY_BRACKET)){
            base = parse_expression(0);
            if(!base) return base;
            if(!match(TokenType::RIGHT_CURLY_BRACKET)){
                return std::unexpected{std::format("\\log subscript missing '}}', found {}", describe_token(peek()))};
            }
        }
        else if(peek().type != TokenType::NUMERIC_LITERAL){
            return std::unexpected{std::format("\\log subscript must be a number, found {}", describe_token(peek()))};
        }
        else {
            if(peek().text.size() == 1) {
                base = std::make_unique<AST>(next());
            }
            else {
                base = split_single_numeric();
                if(!base) return base;
            }
        }
    }

    Token peeked_exponent = peek();
    MaybeAST exponent = nullptr;
    if(match(TokenType::EXPONENT)){
        exponent = match_exponent(0);
        if(!exponent) return exponent;
    }

    const bool using_parentheses = match(TokenType::LEFT_PAREN);
    auto arg = parse_expression(!using_parentheses ? 19 : 0);
    if(!arg) return arg;
    args.emplace_back(std::move(arg.value()));
    if(using_parentheses && !match(TokenType::RIGHT_PAREN)){
        return std::unexpected{std::format("\\log missing closing ')', found {}", describe_token(peek()))};
    }
    return !exponent.value() ? std::make_unique<AST>(token, std::move(args), std::move(base.value()))
        : std::make_unique<AST>(peeked_exponent, std::make_unique<AST>(token, std::move(args), std::move(base.value())), std::move(exponent.value()));
}

dv::MaybeAST dv::Parser::match_builtin_function(const dv::Token &token){
    const auto args_count = builtin_function_args(token.type);
    if(args_count < 1) return std::unexpected{std::format("'{}' requires at least one argument", token.text)};

    if(token.type == TokenType::BUILTIN_FUNC_SQRT) return match_sqrt(token);
    if(token.type == TokenType::BUILTIN_FUNC_LOG) return match_log(token);

    Token peeked_exponent = peek();
    MaybeAST exponent = nullptr;
    if(match(TokenType::EXPONENT)){
        // For function exponents, we use match_exponent with the right binding power
        exponent = match_exponent(30); // Use right binding power of exponent
        if(!exponent) return exponent;
    }

    const bool using_parentheses = match(TokenType::LEFT_PAREN);
    if(!using_parentheses && args_count != 1) {
        return std::unexpected{std::format("'{}' takes {} arguments and requires parentheses", token.text, args_count)};
    }

    std::vector<std::unique_ptr<AST>> args;
    args.reserve(builtin_function_args(token.type));

    if(!using_parentheses){
        auto arg = parse_expression(19);
        if(!arg) return arg;
        args.emplace_back(std::move(arg.value()));

        return !exponent.value() ? std::make_unique<AST>(token, std::move(args))
            : std::make_unique<AST>(peeked_exponent, std::make_unique<AST>(token, std::move(args)), std::move(exponent.value()));
    }

    for(std::uint32_t i = 0; i < args_count - 1; i++){
        auto arg = parse_expression(0);
        if(!arg) return arg;
        if(!match(TokenType::COMMA)) {
            return std::unexpected{std::format("'{}' expects {} arguments, missing ',' after argument {}", token.text, args_count, i + 1)};
        }
        args.emplace_back(std::move(arg.value()));
    }
    auto arg = parse_expression(0);
    if(!arg) return arg;
    if(!match(TokenType::RIGHT_PAREN)) {
        return std::unexpected{std::format("'{}' missing closing ')', found {}", token.text, describe_token(peek()))};
    }
    args.emplace_back(std::move(arg.value()));

    return !exponent.value() ? std::make_unique<AST>(token, std::move(args))
        : std::make_unique<AST>(peeked_exponent, std::make_unique<AST>(token, std::move(args)), std::move(exponent.value()));
}

dv::MaybeAST dv::Parser::match_atom(const dv::Token &token){
    if(token.type == TokenType::NUMERIC_LITERAL) return std::make_unique<AST>(token);
    if(token.type == TokenType::IDENTIFIER) {
        identifier_dependencies.insert(std::string{token.text});
        return std::make_unique<AST>(token);
    }
    if(token.type == TokenType::FORMULA_QUERY) return std::make_unique<AST>(token);
    if(token.type == TokenType::FRACTION) return match_fraction(token);
    if(token.type == TokenType::ABSOLUTE_BAR) return match_absolute_bar(token);
    if(is_builtin_function(token.type)) return match_builtin_function(token);
    return std::unexpected{std::format("Expected a value (number, variable, or function), found {}", describe_token(token))};
}

dv::MaybeAST dv::Parser::match_lhs(const dv::Token &token){
    if(is_atom(token.type)){
        auto lhs = match_atom(token);
        if(!lhs) return lhs;
        if(is_unary_postfix_op(peek().type)){
            return std::make_unique<AST>(next(), std::move(lhs.value()), nullptr);
        }
        return lhs;
    }
    if(token.type == TokenType::LEFT_PAREN){
        auto lhs = parse_expression(0);
        if(!lhs) return lhs;
        if(!match(TokenType::RIGHT_PAREN)) {
            return std::unexpected{std::format("Missing closing ')', found {}", describe_token(peek()))};
        }
        return lhs;
    }
    if(token.type == TokenType::LEFT_ABSOLUTE_BAR) {
        auto lhs = parse_expression(0);
        if(!lhs) return lhs;
        if(!match(TokenType::RIGHT_ABSOLUTE_BAR)) {
            return std::unexpected{std::format("Missing closing '\\right|', found {}", describe_token(peek()))};
        }
        std::vector<std::unique_ptr<AST>> args;
        args.emplace_back(std::move(lhs.value()));
        Token abs_token{TokenType::BUILTIN_FUNC_ABS, "abs"};
        return std::make_unique<AST>(abs_token, std::move(args));
    }
    if(is_unary_prefix_op(token.type)) {
        // For unary prefix, we need to allow atoms, parentheses, or other prefix ops
        // But also need to check we're not at end of expression
        if(peek().type == TokenType::TEOF) return std::unexpected{"Unexpected end of expression after unary operator"};
        if(peek().type == TokenType::RIGHT_PAREN || peek().type == TokenType::RIGHT_BRACKET ||
           peek().type == TokenType::RIGHT_ABSOLUTE_BAR ||
           peek().type == TokenType::RIGHT_CURLY_BRACKET || peek().type == TokenType::COMMA ||
           peek().type == TokenType::ABSOLUTE_BAR) {
            return std::unexpected{std::format("Unary '{}' has no operand, followed by {}", token.text, describe_token(peek()))};
        }
        // Use binding power 15: higher than addition (10) but lower than multiplication (20) and exponent (31)
        // This makes -5+2 parse as (-5)+2, but -(2+3)^2 needs the parentheses to group (2+3) first
        auto rhs = parse_expression(15);
        if(!rhs) return rhs;
        return std::make_unique<AST>(token, std::move(rhs.value()), nullptr);
    }
    return std::unexpected{std::format("Unexpected {} at start of expression", describe_token(token))};
}

dv::MaybeAST dv::Parser::parse_expression(std::int32_t min_binding_power) {
    auto lhs = match_lhs(next());
    if(!lhs) return lhs;
    while (true) {
        Token op = peek();
        if(op.type == TokenType::TEOF) break;
        else if(op.type == TokenType::RIGHT_PAREN) break;
        else if(op.type == TokenType::RIGHT_BRACKET) break;
        else if(op.type == TokenType::RIGHT_CURLY_BRACKET) break;
        else if(op.type == TokenType::RIGHT_ABSOLUTE_BAR) break;
        else if(op.type == TokenType::COMMA) break;
        else if(op.type == TokenType::ABSOLUTE_BAR) break;  // Don't implicit multiply with closing |

        const bool is_implicit_multiplication = !is_binop(op.type);
        if(is_implicit_multiplication) op = {TokenType::TIMES, "*"};

        const auto [ left_binding_power, right_binding_power ] = precedence(op.type);
        if(left_binding_power < min_binding_power) break;

        if(!is_implicit_multiplication) next();

        if(op.type == TokenType::EQUAL) {
            if(has_equal) {
                return std::unexpected{"Expression can only contain one '=' assignment"};
            }
            has_equal = true;
            auto lhs_type = lhs.value()->token.type;
            if(lhs_type != TokenType::IDENTIFIER && lhs_type != TokenType::FORMULA_QUERY) {
                return std::unexpected{"Left side of '=' must be a variable name or '?'"};
            }
        }

        auto rhs = op.type != TokenType::EXPONENT ? parse_expression(right_binding_power) : match_exponent(right_binding_power);
        if(!rhs) return rhs;
        lhs = std::make_unique<AST>(op, std::move(lhs.value()), std::move(rhs.value()));
    }

    return lhs;
}
