#pragma once

#include <string_view>
#include <format>

namespace dv {
    enum class TokenType {
        BAD_IDENTIFIER = -2,
        BAD_NUMERIC = -1,
        UNKNOWN = 0,
        TEOF = 1,
        NUMERIC_LITERAL,
        IDENTIFIER,
        EQUAL,
        PLUS,
        MINUS,
        TIMES,
        FRACTION,
        EXPONENT,
        FACTORIAL,
        ABSOLUTE_BAR,
        COMMA,
        LEFT_CURLY_BRACKET,
        RIGHT_CURLY_BRACKET,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        LEFT_PAREN,
        RIGHT_PAREN,
        BUILTIN_FUNC_LN,
        BUILTIN_FUNC_SIN,
        BUILTIN_FUNC_COS,
        BUILTIN_FUNC_TAN,
        BUILTIN_FUNC_SEC,
        BUILTIN_FUNC_CSC,
        BUILTIN_FUNC_COT,
        BUILTIN_FUNC_LOG,
        BUILTIN_FUNC_ABS,
        BUILTIN_FUNC_NCR,
        BUILTIN_FUNC_NPR,
        BUILTIN_FUNC_SQRT,
        BUILTIN_FUNC_CEIL,
        BUILTIN_FUNC_FACT,
        BUILTIN_FUNC_FLOOR,
        BUILTIN_FUNC_ROUND,
        BUILTIN_FUNC_ARCSIN,
        BUILTIN_FUNC_ARCCOS,
        BUILTIN_FUNC_ARCTAN,
        BUILTIN_FUNC_ARCSEC,
        BUILTIN_FUNC_ARCCSC,
        BUILTIN_FUNC_ARCCOT,
    };
    
    struct Token {
        TokenType type;
        std::string_view text;
        double value;
        Token(): type{TokenType::UNKNOWN}, text{""}, value{0} {}
        Token(const double value, const std::string_view token_text): type{TokenType::NUMERIC_LITERAL}, text{token_text}, value{value} {}
        Token(const TokenType token_type, const std::string_view token_text): type{token_type}, text{token_text}, value{0} {}
        Token(const TokenType token_type, const double token_value, const std::string_view token_text): type{token_type}, text{token_text}, value{token_value} {}
        operator bool() const noexcept{ return type != TokenType::TEOF; }
    };
};
template <>
struct std::formatter<dv::Token> : std::formatter<std::string> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return std::formatter<std::string>::parse(ctx);
    }

    auto format(const dv::Token& token, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "[{}]: \"{}\" = {}", static_cast<std::int32_t>(token.type), token.text, token.value);
    }
};