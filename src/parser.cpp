#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <memory>

bool dv::Parser::match(dv::TokenType type) {
    if (peek().type == type) { position++; return true; }
    return false;
}

std::pair<std::int32_t, std::int32_t> dv::Parser::precedence(dv::TokenType type){
    switch (type) {
        case dv::TokenType::PLUS:
        case dv::TokenType::MINUS:
            return { 11, 10 };
        case dv::TokenType::TIMES:
        case dv::TokenType::FRACTION:
            return { 21, 20 };
        default: return {-1, -1};
    }
}

bool dv::Parser::is_atom(dv::TokenType type) {
    switch(type) {
        case dv::TokenType::NUMERIC_LITERAL:
        case dv::TokenType::IDENTIFIER:
        case dv::TokenType::RIGHT_PAREN:
        case dv::TokenType::RIGHT_BRACKET:
        case dv::TokenType::RIGHT_CURLY_BRACKET:
        case dv::TokenType::FACTORIAL:
        case dv::TokenType::ABSOLUTE_BAR:
            return true;
        default: return false;
    }
}

bool dv::Parser::is_implicit_atom(dv::TokenType type) {
    switch(type) {
        case dv::TokenType::NUMERIC_LITERAL:
        case dv::TokenType::IDENTIFIER:
        case dv::TokenType::LEFT_PAREN:
        case dv::TokenType::LEFT_BRACKET:
        case dv::TokenType::LEFT_CURLY_BRACKET:
        case dv::TokenType::ABSOLUTE_BAR:
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
            return true;
        default:
            return false;
    }
}

std::unique_ptr<dv::AST> dv::Parser::match_lhs(const dv::Token &token){
    if(is_atom(token.type)){
        if(token.type == TokenType::NUMERIC_LITERAL) return std::make_unique<AST>(token);
    }
    else if(token.type == TokenType::LEFT_PAREN){
        auto lhs = parse_expression(0);
        if(!match(TokenType::RIGHT_PAREN)) throw "MISSING RIGHT PAREN";
        return lhs;
    }
    throw "BAD TOKEN";
}
std::unique_ptr<dv::AST> dv::Parser::parse_expression(std::int32_t min_binding_power) {
    std::unique_ptr<AST> lhs = match_lhs(next());
    while (true) {
        Token op = peek();
        if(op.type == TokenType::TEOF) break;
        else if(op.type == TokenType::RIGHT_PAREN) break;

        next();
        const auto [ left_binding_power, right_binding_power ] = precedence(op.type);
        if(left_binding_power < min_binding_power) break;
        auto rhs = parse_expression(right_binding_power);
        lhs = std::make_unique<AST>(op, std::move(lhs), std::move(rhs));
        // implicit multiplication
        // if (isAtom(lhs.lastToken) && is_implicit_atom(op)) {
        //     op = TokenType::TIMES;
        // }

        // int prec = precedence(op);
        // if (prec < minPrec) break;

        // bool rightAssoc = (op == TokenType::EXPONENT);
        // next();

        // AST right = parse_expression(prec + (rightAssoc ? 0 : 1));
        // lhs = makeBinary(op, lhs, right);
    }

    return lhs;
}
