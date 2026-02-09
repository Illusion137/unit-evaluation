#pragma once

#include "token.hpp"
#include "ast.hpp"
#include <expected>
#include <memory>
#include <vector>

namespace dv {
    class Parser {
    public:
        Parser(const std::vector<dv::Token> &token_list): tokens{token_list} {}
        using MaybeAST = std::expected<std::unique_ptr<AST>, std::string>;
        inline MaybeAST parse() { return parse_expression(0); }
    private:
        std::vector<dv::Token> tokens;
        std::size_t position = 0;
    
        inline Token& peek() { return tokens[position]; }
        inline Token& peek_next() { return tokens[position + 1]; }
        inline Token& next() { return tokens[position++]; }

        bool match(dv::TokenType type);
        
        // negative values mean varadic args
        std::int32_t builtin_function_args(dv::TokenType type);
        std::pair<std::int32_t, std::int32_t> precedence(dv::TokenType type);
        bool is_atom(dv::TokenType type);
        bool is_binop(dv::TokenType type);
        bool is_builtin_function(dv::TokenType type);
        bool is_unary_prefix_op(dv::TokenType type);
        bool is_unary_postfix_op(dv::TokenType type);
        bool can_implicit_multiply_left(const Token& token);
        MaybeAST split_single_numeric();
        MaybeAST match_atom(const dv::Token &token);
        MaybeAST match_lhs(const dv::Token &token);
        MaybeAST match_square_bracket();
        MaybeAST match_curly_bracket();
        MaybeAST match_parentheses();
        MaybeAST match_absolute_bar(const dv::Token &token);
        MaybeAST match_sqrt(const dv::Token &token);
        MaybeAST match_log(const dv::Token &token);
        MaybeAST match_builtin_function(const dv::Token &token);
        MaybeAST match_fraction(const dv::Token &token);
        MaybeAST match_exponent(std::int32_t right_binding_power);
        MaybeAST parse_expression(std::int32_t min_binding_power);
    };
}