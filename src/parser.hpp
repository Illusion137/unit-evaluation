#pragma once

#include "token.hpp"
#include "ast.hpp"
#include <memory>
#include <vector>

namespace dv {
    class Parser {
    public:
        Parser(const std::vector<dv::Token> &token_list): tokens{token_list} {}
        inline std::unique_ptr<AST> parse() { return parse_expression(0); }
    private:
        std::vector<dv::Token> tokens;
        std::size_t position = 0;
    
        inline Token& peek() { return tokens[position]; }
        inline Token& next() { return tokens[position++]; }

        bool match(dv::TokenType type);
        
        std::pair<std::int32_t, std::int32_t> precedence(dv::TokenType type);
        bool is_atom(dv::TokenType type);
        bool is_implicit_atom(dv::TokenType type);
        AST *parse_unary();
        AST *parse_postfix();
        AST *parse_atom();
        std::unique_ptr<AST> match_lhs(const dv::Token &token);
        std::unique_ptr<AST> parse_expression(std::int32_t min_binding_power);
    };
}