#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <memory>
#include <print>
#include <vector>

bool dv::Parser::match(dv::TokenType type) {
    if (peek().type == type) { position++; return true; }
    return false;
}

std::pair<std::int32_t, std::int32_t> dv::Parser::precedence(dv::TokenType type){
    switch (type) {
        case dv::TokenType::PLUS:
        case dv::TokenType::MINUS:
            return { 10, 11 };
        case dv::TokenType::TIMES:
        case dv::TokenType::DIVIDE:
            return { 20, 21 };
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
            return true;
        default: return false;
    }
}
bool dv::Parser::can_implicit_multiply_left(const AST& ast) {
    return is_atom(ast.token.type);
}

std::unique_ptr<dv::AST> dv::Parser::match_curly(){
    match(TokenType::LEFT_CURLY_BRACKET);
    auto ast = parse_expression(0);
    match(TokenType::RIGHT_CURLY_BRACKET);
    return ast;
}

std::unique_ptr<dv::AST> dv::Parser::match_fraction(const dv::Token &token){
    std::unique_ptr<dv::AST> numerator = match_curly();
    std::unique_ptr<dv::AST> denominator = match_curly();
    return std::make_unique<AST>(token, std::move(numerator), std::move(denominator));
}

std::unique_ptr<dv::AST> dv::Parser::match_builtin_function(const dv::Token &token){
    bool openparen = match(TokenType::LEFT_PAREN);
    std::unique_ptr<AST> arg = nullptr;
    if(openparen) arg = parse_expression(0);
    else arg = parse_expression(0);
    return std::make_unique<AST>(token, std::move(arg), nullptr);
}

std::unique_ptr<dv::AST> dv::Parser::match_lhs(const dv::Token &token){
    if(is_atom(token.type)){
        if(token.type == TokenType::NUMERIC_LITERAL) return std::make_unique<AST>(token);
        if(token.type == TokenType::FRACTION) return match_fraction(token);
        if(is_builtin_function(token.type)) return match_builtin_function(token);
        // TODO fill this
    }
    if(token.type == TokenType::LEFT_PAREN){
        auto lhs = parse_expression(0);
        if(!match(TokenType::RIGHT_PAREN)) throw "MISSING RIGHT PAREN";
        return lhs;
    }
    return std::make_unique<AST>(token);
}
std::unique_ptr<dv::AST> dv::Parser::parse_expression(std::int32_t min_binding_power) {
    std::unique_ptr<AST> lhs = match_lhs(next());
    while (true) {
        Token op = peek();
        if(op.type == TokenType::TEOF) break;
        else if(op.type == TokenType::RIGHT_PAREN) break;
        else if(op.type == TokenType::RIGHT_CURLY_BRACKET) break;
        
        const bool is_implicit_multiplication = !is_binop(op.type);
        if(is_implicit_multiplication) op = {TokenType::TIMES, "*"};
        
        const auto [ left_binding_power, right_binding_power ] = precedence(op.type);
        if(left_binding_power < min_binding_power) break;

        if(!is_implicit_multiplication) next();

        auto rhs = parse_expression(right_binding_power);
        lhs = std::make_unique<AST>(op, std::move(lhs), std::move(rhs));
    }

    return lhs;
}
