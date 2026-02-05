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
    };
    
    extern dv::EValue eval(const std::unique_ptr<AST> &ast);
}
