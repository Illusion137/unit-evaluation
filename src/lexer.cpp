#include "lexer.hpp"
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <expected>

#define M_PI 3.14159265358979323846264338327950288

template <std::size_t N>
struct LiteralString {
    consteval LiteralString(const char (&s)[N]) { std::copy(s, s + N - 1, &data[0]); }

    static constexpr std::size_t size = N - 1;
    char data[N]{};
};

template <LiteralString str>
consteval std::uint64_t strint(){
    std::uint64_t val = 0;
    for(std::uint32_t i = 0; i < str.size; i++){
        val |= (std::uint64_t)str.data[i] << (8 * i);
    }
    return val;
}
constexpr std::uint64_t strint(const char *str, std::size_t size){
    std::uint64_t val = 0;
    for(std::uint32_t i = 0; i < size; i++){
        val |= (std::uint64_t)str[i] << (8 * i);
    }
    return val;
}

constexpr bool isnumeric(char c){
    return std::isdigit(c) || c == '.';
}

dv::Lexer::Lexer(const std::string_view view) noexcept{
    begin = view.data();
    it = begin;
    length = view.size();
}
dv::Lexer::MaybeTokens dv::Lexer::extract_all_tokens() noexcept{
    std::vector<Token> tokens;
    tokens.reserve(length / 2);
    Token token;
    while((token = consume_next_token()).type != TokenType::TEOF){
        if(token.has_error()) {
            return std::unexpected{token.get_error_message()};
        }
        tokens.emplace_back(std::move(token));
    }
    tokens.emplace_back(TokenType::TEOF, "");
    return tokens;
}

std::uint32_t dv::Lexer::remaining_length() const noexcept { return length - (begin - it); }
char dv::Lexer::peek() const noexcept { return *it; }
char dv::Lexer::peek_next() const noexcept { return *(it + 1); }
void dv::Lexer::advance() noexcept { it++; }
void dv::Lexer::advance(const std::uint32_t count) noexcept { it += count; }
dv::Token dv::Lexer::advance_with_token(const TokenType token_type) noexcept { 
    it++;
    return {token_type, {it - 1, 1}};
}
dv::Token dv::Lexer::advance_with_token(const TokenType token_type, const std::uint32_t count) noexcept {
    it += count;
    return {token_type, {it - count, count}};
}
dv::Token dv::Lexer::advance_with_token(const double token_value, const std::uint32_t count) noexcept {
    it += count;
    return {token_value, {it - count, count}};
}

dv::Token dv::Lexer::get_numeric_literal_token() noexcept{
    const char *begit = it;
    bool used_decimal = false;
    std::array<char, 32> buffer;
    buffer.fill(0);
    std::uint8_t write = 0;
    buffer[write++] = peek();
    if(peek() == '.') used_decimal = true;
    advance();
    char c;
    while((c = peek()) && (std::isdigit(c) || c == '.') && write < buffer.size()){
        if(used_decimal && c == '.') return {TokenType::BAD_NUMERIC, begit};
        if(c == '.') used_decimal = true;
        buffer[write++] = c;
        advance();
    }
    return {std::atof(buffer.data()), {begit, it}};
}

std::int32_t dv::Lexer::collect_subscript(char *buffer, std::size_t size, std::uint8_t &write) noexcept{
    if(peek() == '_' && peek_next() == '{') {
        buffer[write++] = '_';
        buffer[write++] = '{';
        advance(2);
        char c;
        while((c = peek()) && c != '}' && write < size){
            buffer[write++] = c;
            advance();
        }
        if(peek() == '}'){
            buffer[write++] = '}';
            advance();
        }
        else return 0;
    }
    else if(peek() == '_' && std::isalnum(peek_next())){
        buffer[write++] = '_';
        buffer[write++] = peek_next();
        advance(2);
    }
    return 1;
}

dv::Token dv::Lexer::get_indentifier_token(std::uint32_t max_length) noexcept{
    const char *begit = it;
    std::array<char, 32> buffer;
    buffer.fill(0);
    std::uint8_t write = 0;
    char c;
    while((c = peek()) && std::isalpha(c) && write < buffer.size() && write < max_length){
        buffer[write++] = c;
        advance();
    }
    if(write >= 1) {
        if(!collect_subscript(buffer.data(), buffer.size(), write)) {
            return {TokenType::BAD_IDENTIFIER, begit};
        }
    }
    return {TokenType::IDENTIFIER, {begit, it}};
}
dv::Token dv::Lexer::get_special_indentifier_token() noexcept{
    advance();
        if(remaining_length() >= 8) {
        switch(strint(it, 8)) {
            case strint<"sin^{-1}">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCSIN, 8);
            case strint<"cos^{-1}">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCCOS, 8);
            case strint<"tan^{-1}">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCTAN, 8);
            case strint<"sec^{-1}">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCSEC, 8);
            case strint<"csc^{-1}">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCCSC, 8);
            case strint<"cot^{-1}">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCCOT, 8);
            default: break;
        }
    }
    if(remaining_length() >= 6) {
        switch(strint(it, 6)) {
            case strint<"arcsin">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCSIN, 6);
            case strint<"arccos">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCCOS, 6);
            case strint<"arctan">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCTAN, 6);
            case strint<"arcsec">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCSEC, 6);
            case strint<"arccsc">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCCSC, 6);
            case strint<"arccot">(): return advance_with_token(TokenType::BUILTIN_FUNC_ARCCOT, 6);
            case strint<"right)">(): return advance_with_token(TokenType::RIGHT_PAREN, 6);
            default: break;
        }
    }
    if(remaining_length() >= 5) {
        switch(strint(it, 5)) {
            case strint<"floor">(): return advance_with_token(TokenType::BUILTIN_FUNC_FLOOR, 5);
            case strint<"round">(): return advance_with_token(TokenType::BUILTIN_FUNC_ROUND, 5);
            case strint<"times">(): return advance_with_token(TokenType::TIMES, 5);
            case strint<"left(">(): return advance_with_token(TokenType::LEFT_PAREN, 5);
            default: break;
        }
    }
    if(remaining_length() >= 4) {
        switch(*(std::uint32_t*)it) {
            case strint<"sqrt">(): return advance_with_token(TokenType::BUILTIN_FUNC_SQRT, 4);
            case strint<"ceil">(): return advance_with_token(TokenType::BUILTIN_FUNC_CEIL, 4);
            case strint<"fact">(): return advance_with_token(TokenType::BUILTIN_FUNC_FACT, 4);
            case strint<"frac">(): return advance_with_token(TokenType::FRACTION, 4);
            case strint<"cdot">(): return advance_with_token(TokenType::TIMES, 4);
            default: break;
        }
    }
    if(remaining_length() >= 3) {
        switch(strint(it, 3)) {
            case strint<"sin">(): return advance_with_token(TokenType::BUILTIN_FUNC_SIN, 3);
            case strint<"cos">(): return advance_with_token(TokenType::BUILTIN_FUNC_COS, 3);
            case strint<"tan">(): return advance_with_token(TokenType::BUILTIN_FUNC_TAN, 3);
            case strint<"sec">(): return advance_with_token(TokenType::BUILTIN_FUNC_SEC, 3);
            case strint<"csc">(): return advance_with_token(TokenType::BUILTIN_FUNC_CSC, 3);
            case strint<"cot">(): return advance_with_token(TokenType::BUILTIN_FUNC_COT, 3);
            case strint<"abs">(): return advance_with_token(TokenType::BUILTIN_FUNC_ABS, 3);
            case strint<"nCr">(): return advance_with_token(TokenType::BUILTIN_FUNC_NCR, 3);
            case strint<"nPr">(): return advance_with_token(TokenType::BUILTIN_FUNC_NPR, 3);
            case strint<"log">(): return advance_with_token(TokenType::BUILTIN_FUNC_LOG, 3);
            default: break;
        }
    }
    if(remaining_length() >= 2) {
        switch(*(std::uint16_t*)it) {
            case strint<"pi">(): return advance_with_token(M_PI, 2);
            case strint<"ln">(): return advance_with_token(TokenType::BUILTIN_FUNC_LN, 2);
            default: break;
        }
    }
    return get_indentifier_token();
}

void dv::Lexer::devoure_whitespace() noexcept{
    while(std::isspace(peek())) advance();
}

dv::Token dv::Lexer::consume_next_token() noexcept{
    devoure_whitespace();
    if(!peek()) return {TokenType::TEOF, ""};
    switch (peek()) {
        case '_': return advance_with_token(TokenType::SUBSCRIPT);
        case '=': return advance_with_token(TokenType::EQUAL);
        case ',': return advance_with_token(TokenType::COMMA);
        case '+': return advance_with_token(TokenType::PLUS);
        case '-': return advance_with_token(TokenType::MINUS);
        case '*': return advance_with_token(TokenType::TIMES);
        case '/': return advance_with_token(TokenType::DIVIDE);
        case '^': return advance_with_token(TokenType::EXPONENT);
        case '!': return advance_with_token(TokenType::FACTORIAL);
        case '(': return advance_with_token(TokenType::LEFT_PAREN);
        case ')': return advance_with_token(TokenType::RIGHT_PAREN);
        case '{': return advance_with_token(TokenType::LEFT_CURLY_BRACKET);
        case '}': return advance_with_token(TokenType::RIGHT_CURLY_BRACKET);
        case '[': return advance_with_token(TokenType::LEFT_BRACKET);
        case ']': return advance_with_token(TokenType::RIGHT_BRACKET);
        case '|': return advance_with_token(TokenType::ABSOLUTE_BAR);
        case '\\': return get_special_indentifier_token();
        default: {
            if(isnumeric(peek())) return get_numeric_literal_token();
            if(std::isalpha(peek())) return get_indentifier_token(1);
        };
    }
    return {TokenType::UNKNOWN, it};
}