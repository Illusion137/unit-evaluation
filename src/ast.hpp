#pragma once

#include "dimeval.hpp"
#include "token.hpp"
#include <memory>

namespace dv {
    struct AST {
        Token token;
        std::unique_ptr<AST> lhs = nullptr;
        std::unique_ptr<AST> rhs = nullptr;
        dv::EValue value;
        AST(): token(TokenType::UNKNOWN, ""), value(0.0) {}
        AST(const Token token): token(token), value(token.value) {}
        AST(const Token token, std::unique_ptr<AST> lhs, std::unique_ptr<AST> rhs): token{token}, lhs{std::move(lhs)}, rhs{std::move(rhs)}, value(0.0) {}
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