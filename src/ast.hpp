#pragma once

#include "dimeval.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <variant>

namespace dv {
    struct AST {
        struct ASTExpression {
            std::unique_ptr<AST> lhs;
            std::unique_ptr<AST> rhs;
            dv::EValue value;
        };
        struct ASTCall {
            std::vector<std::unique_ptr<AST>> args;
            std::unique_ptr<AST> special_value;
        };
        Token token;
        std::variant<ASTExpression, ASTCall> data;
        
        AST(): token(TokenType::UNKNOWN, ""), data{ASTExpression{nullptr, nullptr, 0.0}}{}
        AST(const Token token): token(token), data(ASTExpression{nullptr, nullptr, token.value}) {}
        AST(const Token token, std::unique_ptr<AST> lhs, std::unique_ptr<AST> rhs): token{token}, data{ASTExpression{std::move(lhs), std::move(rhs), 0.0}} {}
        AST(const Token token, std::vector<std::unique_ptr<AST>> args, std::unique_ptr<AST> special_value = nullptr): token{token}, data{ASTCall{std::move(args), std::move(special_value)}} {}
        dv::EValue evaluate();
        dv::EValue evaluate(const AST *ast);
        dv::EValue evaluate(const std::unique_ptr<AST> &ast);
        std::string to_string(const std::uint16_t depth = 0) const noexcept;
    };
}
template <>
struct std::formatter<dv::AST> : std::formatter<std::string> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return std::formatter<std::string>::parse(ctx);
    }

    auto format(const dv::AST& ast, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", ast.to_string());  
    }
};