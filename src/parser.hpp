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
        bool is_binop(dv::TokenType type);
        bool is_builtin_function(dv::TokenType type);
        bool can_implicit_multiply_left(const AST& ast);
        std::unique_ptr<AST> match_lhs(const dv::Token &token);
        std::unique_ptr<dv::AST> match_curly();
        std::unique_ptr<dv::AST> match_fraction(const dv::Token &token);
        std::unique_ptr<dv::AST> match_builtin_function(const dv::Token &token);
        std::unique_ptr<AST> parse_expression(std::int32_t min_binding_power);
    };
}