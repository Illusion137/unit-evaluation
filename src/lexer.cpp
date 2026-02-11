#include "lexer.hpp"
#include "dimeval.hpp"
#include "token.hpp"
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <expected>

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
dv::Token dv::Lexer::advance_with_token(const EValue token_value, const std::uint32_t count) noexcept {
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

std::int32_t dv::Lexer::collect_curly_brackets(char *buffer, std::size_t size, std::uint8_t &write) noexcept{
    if(peek() == '{') {
        advance(1);
        char c;
        while((c = peek()) && c != '}' && write < size){
            buffer[write++] = c;
            advance();
        }
        if(peek() == '}'){
            advance();
        }
        else return 0;
    }
    else return 0;
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
            case strint<"right|">(): return advance_with_token(TokenType::RIGHT_ABSOLUTE_BAR, 6);
            default: break;
        }
    }
    if(remaining_length() >= 5) {
        switch(strint(it, 5)) {
            case strint<"floor">(): return advance_with_token(TokenType::BUILTIN_FUNC_FLOOR, 5);
            case strint<"round">(): return advance_with_token(TokenType::BUILTIN_FUNC_ROUND, 5);
            case strint<"times">(): return advance_with_token(TokenType::TIMES, 5);
            case strint<"left(">(): return advance_with_token(TokenType::LEFT_PAREN, 5);
            case strint<"left|">(): return advance_with_token(TokenType::LEFT_ABSOLUTE_BAR, 5);
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
    if(remaining_length() >= 12){
        const std::int32_t result = memcmp(it, "operatorname", sizeof(char) * 12);
        if(result == 0){
            advance(12);
            std::array<char, 32> buffer;
            std::uint8_t write = 0;
            buffer.fill(0);
            auto result = collect_curly_brackets(buffer.data(), buffer.size(), write);
            if(!result) return {TokenType::UNKNOWN, "Bad Operator name result"};
            if(write >= 5) {
                switch(strint(buffer.data(), 5)) {
                    case strint<"floor">(): return advance_with_token(TokenType::BUILTIN_FUNC_FLOOR, 0);
                    case strint<"round">(): return advance_with_token(TokenType::BUILTIN_FUNC_ROUND, 0);
                    default: break;
                }
            }
            if(write >= 4) {
                switch(*(std::uint32_t*)buffer.data()) {
                    case strint<"ceil">(): return advance_with_token(TokenType::BUILTIN_FUNC_CEIL, 0);
                    case strint<"fact">(): return advance_with_token(TokenType::BUILTIN_FUNC_FACT, 0);
                    default: break;
                }
            }
            if(write >= 3) {
                switch(strint(buffer.data(), 3)) {
                    case strint<"abs">(): return advance_with_token(TokenType::BUILTIN_FUNC_ABS, 0);
                    case strint<"nCr">(): return advance_with_token(TokenType::BUILTIN_FUNC_NCR, 0);
                    case strint<"nPr">(): return advance_with_token(TokenType::BUILTIN_FUNC_NPR, 0);
                    default: break;
                }
            }
            return {TokenType::UNKNOWN, "Bad Operator name"};
        }
    }
    auto unit_token = get_unit_token();
    if(unit_token.type != TokenType::UNKNOWN) return unit_token;
    return get_indentifier_token();
}

#define UNIT_CASE(str, value, unit) case strint<str>(): return advance_with_token(dv::EValue{value, unit}, sizeof(str) - 1)
#define UNIT_CASE_LIST_BEGIN(size) if(remaining_length() >= size) { switch(strint(it, size)) { default: break;
#define UNIT_CASE_LIST_END(size) }}
dv::Token dv::Lexer::get_unit_token() noexcept {
    UNIT_CASE_LIST_BEGIN(6)

    UNIT_CASE_LIST_END()
    UNIT_CASE_LIST_BEGIN(5)

    UNIT_CASE_LIST_END()
    UNIT_CASE_LIST_BEGIN(4)

    UNIT_CASE_LIST_END()
    UNIT_CASE_LIST_BEGIN(3)

    UNIT_CASE_LIST_END()
    UNIT_CASE_LIST_BEGIN(2)

    UNIT_CASE_LIST_END()
    UNIT_CASE_LIST_BEGIN(1)

    UNIT_CASE_LIST_END()
    if(remaining_length() >= 4) {
        switch(*(std::uint64_t*)it) {
            UNIT_CASE("am", 1e-18, DIM_METER);
            UNIT_CASE("as", 1e-18, DIM_SECOND);
            UNIT_CASE("ag", 1e-21, DIM_KILOGRAM);
            UNIT_CASE("aA", 1e-18, DIM_AMPERE);
            UNIT_CASE("aK", 1e-18, DIM_KILOGRAM);
            UNIT_CASE("acd", 1e-18, DIM_CANDELA);
            UNIT_CASE("aN", 1e-18, DIM_NEWTON);
            UNIT_CASE("aJ", 1e-18, DIM_JOULE);
            UNIT_CASE("aPa", 1e-18, DIM_PASCAL);
            UNIT_CASE("aC", 1e-18, DIM_COULOMB);
            UNIT_CASE("aHz", 1e-18, DIM_HERTZ);
            UNIT_CASE("aS", 1e-18, DIM_SIEMENS);
            UNIT_CASE("aOhm", 1e-18, DIM_OHM);
            UNIT_CASE("aF", 1e-18, DIM_FARAD);
            UNIT_CASE("aV", 1e-18, DIM_VOLT);
            UNIT_CASE("aW", 1e-18, DIM_WATT);

            UNIT_CASE("fm", 1e-15, DIM_METER);
            UNIT_CASE("fs", 1e-15, DIM_SECOND);
            UNIT_CASE("fg", 1e-18, DIM_KILOGRAM);
            UNIT_CASE("fA", 1e-15, DIM_AMPERE);
            UNIT_CASE("fK", 1e-15, DIM_KILOGRAM);
            UNIT_CASE("fcd", 1e-15, DIM_CANDELA);
            UNIT_CASE("fN", 1e-15, DIM_NEWTON);
            UNIT_CASE("fJ", 1e-15, DIM_JOULE);
            UNIT_CASE("fPa", 1e-15, DIM_PASCAL);
            UNIT_CASE("fC", 1e-15, DIM_COULOMB);
            UNIT_CASE("fHz", 1e-15, DIM_HERTZ);
            UNIT_CASE("fS", 1e-15, DIM_SIEMENS);
            UNIT_CASE("fOhm", 1e-15, DIM_OHM);
            UNIT_CASE("fF", 1e-15, DIM_FARAD);
            UNIT_CASE("fV", 1e-15, DIM_VOLT);
            UNIT_CASE("fW", 1e-15, DIM_WATT);

            UNIT_CASE("pm", 1e-12, DIM_METER);
            UNIT_CASE("ps", 1e-12, DIM_SECOND);
            UNIT_CASE("pg", 1e-15, DIM_KILOGRAM);
            UNIT_CASE("pA", 1e-12, DIM_AMPERE);
            UNIT_CASE("pK", 1e-12, DIM_KILOGRAM);
            UNIT_CASE("pcd", 1e-12, DIM_CANDELA);
            UNIT_CASE("pN", 1e-12, DIM_NEWTON);
            UNIT_CASE("pJ", 1e-12, DIM_JOULE);
            UNIT_CASE("pPa", 1e-12, DIM_PASCAL);
            UNIT_CASE("pC", 1e-12, DIM_COULOMB);
            UNIT_CASE("pHz", 1e-12, DIM_HERTZ);
            UNIT_CASE("pS", 1e-12, DIM_SIEMENS);
            UNIT_CASE("pOhm", 1e-12, DIM_OHM);
            UNIT_CASE("pF", 1e-12, DIM_FARAD);
            UNIT_CASE("pV", 1e-12, DIM_VOLT);
            UNIT_CASE("pW", 1e-12, DIM_WATT);

            UNIT_CASE("nm", 1e-9, DIM_METER);
            UNIT_CASE("ns", 1e-9, DIM_SECOND);
            UNIT_CASE("ng", 1e-12, DIM_KILOGRAM);
            UNIT_CASE("nA", 1e-9, DIM_AMPERE);
            UNIT_CASE("nK", 1e-9, DIM_KILOGRAM);
            UNIT_CASE("ncd", 1e-9, DIM_CANDELA);
            UNIT_CASE("nN", 1e-9, DIM_NEWTON);
            UNIT_CASE("nJ", 1e-9, DIM_JOULE);
            UNIT_CASE("nPa", 1e-9, DIM_PASCAL);
            UNIT_CASE("nC", 1e-9, DIM_COULOMB);
            UNIT_CASE("nHz", 1e-9, DIM_HERTZ);
            UNIT_CASE("nS", 1e-9, DIM_SIEMENS);
            UNIT_CASE("nOhm", 1e-9, DIM_OHM);
            UNIT_CASE("nF", 1e-9, DIM_FARAD);
            UNIT_CASE("nV", 1e-9, DIM_VOLT);
            UNIT_CASE("nW", 1e-9, DIM_WATT);

            UNIT_CASE("mu m", 1e-6, DIM_METER);
            UNIT_CASE("mu s", 1e-6, DIM_SECOND);
            UNIT_CASE("mu g", 1e-9, DIM_KILOGRAM);
            UNIT_CASE("mu A", 1e-6, DIM_AMPERE);
            UNIT_CASE("mu K", 1e-6, DIM_KILOGRAM);
            UNIT_CASE("mu cd", 1e-6, DIM_CANDELA);
            UNIT_CASE("mu N", 1e-6, DIM_NEWTON);
            UNIT_CASE("mu J", 1e-6, DIM_JOULE);
            UNIT_CASE("mu Pa", 1e-6, DIM_PASCAL);
            UNIT_CASE("mu C", 1e-6, DIM_COULOMB);
            UNIT_CASE("mu Hz", 1e-6, DIM_HERTZ);
            UNIT_CASE("mu S", 1e-6, DIM_SIEMENS);
            UNIT_CASE("mu Ohm", 1e-6, DIM_OHM);
            UNIT_CASE("mu F", 1e-6, DIM_FARAD);
            UNIT_CASE("mu V", 1e-6, DIM_VOLT);
            UNIT_CASE("mu W", 1e-6, DIM_WATT);

            UNIT_CASE("mm", 1e-3, DIM_METER);
            UNIT_CASE("ms", 1e-3, DIM_SECOND);
            UNIT_CASE("mg", 1e-6, DIM_KILOGRAM);
            UNIT_CASE("mA", 1e-3, DIM_AMPERE);
            UNIT_CASE("mK", 1e-3, DIM_KILOGRAM);
            UNIT_CASE("mcd", 1e-3, DIM_CANDELA);
            UNIT_CASE("mN", 1e-3, DIM_NEWTON);
            UNIT_CASE("mJ", 1e-3, DIM_JOULE);
            UNIT_CASE("mPa", 1e-3, DIM_PASCAL);
            UNIT_CASE("mC", 1e-3, DIM_COULOMB);
            UNIT_CASE("mHz", 1e-3, DIM_HERTZ);
            UNIT_CASE("mS", 1e-3, DIM_SIEMENS);
            UNIT_CASE("mOhm", 1e-3, DIM_OHM);
            UNIT_CASE("mF", 1e-3, DIM_FARAD);
            UNIT_CASE("mV", 1e-3, DIM_VOLT);
            UNIT_CASE("mW", 1e-3, DIM_WATT);

            UNIT_CASE("cm", 1e-2, DIM_METER);
            UNIT_CASE("cs", 1e-2, DIM_SECOND);
            UNIT_CASE("cg", 1e-5, DIM_KILOGRAM);
            UNIT_CASE("cA", 1e-2, DIM_AMPERE);
            UNIT_CASE("cK", 1e-2, DIM_KILOGRAM);
            UNIT_CASE("ccd", 1e-2, DIM_CANDELA);
            UNIT_CASE("cN", 1e-2, DIM_NEWTON);
            UNIT_CASE("cJ", 1e-2, DIM_JOULE);
            UNIT_CASE("cPa", 1e-2, DIM_PASCAL);
            UNIT_CASE("cC", 1e-2, DIM_COULOMB);
            UNIT_CASE("cHz", 1e-2, DIM_HERTZ);
            UNIT_CASE("cS", 1e-2, DIM_SIEMENS);
            UNIT_CASE("cOhm", 1e-2, DIM_OHM);
            UNIT_CASE("cF", 1e-2, DIM_FARAD);
            UNIT_CASE("cV", 1e-2, DIM_VOLT);
            UNIT_CASE("cW", 1e-2, DIM_WATT);

            UNIT_CASE("dm", 1e-1, DIM_METER);
            UNIT_CASE("ds", 1e-1, DIM_SECOND);
            UNIT_CASE("dg", 1e-4, DIM_KILOGRAM);
            UNIT_CASE("dA", 1e-1, DIM_AMPERE);
            UNIT_CASE("dK", 1e-1, DIM_KILOGRAM);
            UNIT_CASE("dcd", 1e-1, DIM_CANDELA);
            UNIT_CASE("dN", 1e-1, DIM_NEWTON);
            UNIT_CASE("dJ", 1e-1, DIM_JOULE);
            UNIT_CASE("dPa", 1e-1, DIM_PASCAL);
            UNIT_CASE("dC", 1e-1, DIM_COULOMB);
            UNIT_CASE("dHz", 1e-1, DIM_HERTZ);
            UNIT_CASE("dS", 1e-1, DIM_SIEMENS);
            UNIT_CASE("dOhm", 1e-1, DIM_OHM);
            UNIT_CASE("dF", 1e-1, DIM_FARAD);
            UNIT_CASE("dV", 1e-1, DIM_VOLT);
            UNIT_CASE("dW", 1e-1, DIM_WATT);

            UNIT_CASE("m", 1, DIM_METER);
            UNIT_CASE("s", 1, DIM_SECOND);
            UNIT_CASE("g", 1e-3, DIM_KILOGRAM);
            UNIT_CASE("A", 1, DIM_AMPERE);
            UNIT_CASE("K", 1, DIM_KILOGRAM);
            UNIT_CASE("cd", 1, DIM_CANDELA);
            UNIT_CASE("N", 1, DIM_NEWTON);
            UNIT_CASE("J", 1, DIM_JOULE);
            UNIT_CASE("Pa", 1, DIM_PASCAL);
            UNIT_CASE("C", 1, DIM_COULOMB);
            UNIT_CASE("Hz", 1, DIM_HERTZ);
            UNIT_CASE("S", 1, DIM_SIEMENS);
            UNIT_CASE("Ohm", 1, DIM_OHM);
            UNIT_CASE("F", 1, DIM_FARAD);
            UNIT_CASE("V", 1, DIM_VOLT);
            UNIT_CASE("W", 1, DIM_WATT);

            UNIT_CASE("km", 1e+3, DIM_METER);
            UNIT_CASE("ks", 1e+3, DIM_SECOND);
            UNIT_CASE("kg", 1, DIM_KILOGRAM);
            UNIT_CASE("kA", 1e+3, DIM_AMPERE);
            UNIT_CASE("kK", 1e+3, DIM_KILOGRAM);
            UNIT_CASE("kcd", 1e+3, DIM_CANDELA);
            UNIT_CASE("kN", 1e+3, DIM_NEWTON);
            UNIT_CASE("kJ", 1e+3, DIM_JOULE);
            UNIT_CASE("kPa", 1e+3, DIM_PASCAL);
            UNIT_CASE("kC", 1e+3, DIM_COULOMB);
            UNIT_CASE("kHz", 1e+3, DIM_HERTZ);
            UNIT_CASE("kS", 1e+3, DIM_SIEMENS);
            UNIT_CASE("kOhm", 1e+3, DIM_OHM);
            UNIT_CASE("kF", 1e+3, DIM_FARAD);
            UNIT_CASE("kV", 1e+3, DIM_VOLT);
            UNIT_CASE("kW", 1e+3, DIM_WATT);

            UNIT_CASE("Mm", 1e+6, DIM_METER);
            UNIT_CASE("Ms", 1e+6, DIM_SECOND);
            UNIT_CASE("Mg", 1e+3, DIM_KILOGRAM);
            UNIT_CASE("MA", 1e+6, DIM_AMPERE);
            UNIT_CASE("MK", 1e+6, DIM_KILOGRAM);
            UNIT_CASE("Mcd", 1e+6, DIM_CANDELA);
            UNIT_CASE("MN", 1e+6, DIM_NEWTON);
            UNIT_CASE("MJ", 1e+6, DIM_JOULE);
            UNIT_CASE("MPa", 1e+6, DIM_PASCAL);
            UNIT_CASE("MC", 1e+6, DIM_COULOMB);
            UNIT_CASE("MHz", 1e+6, DIM_HERTZ);
            UNIT_CASE("MS", 1e+6, DIM_SIEMENS);
            UNIT_CASE("MOhm", 1e+6, DIM_OHM);
            UNIT_CASE("MF", 1e+6, DIM_FARAD);
            UNIT_CASE("MV", 1e+6, DIM_VOLT);
            UNIT_CASE("MW", 1e+6, DIM_WATT);

            UNIT_CASE("Gm", 1e+9, DIM_METER);
            UNIT_CASE("Gs", 1e+9, DIM_SECOND);
            UNIT_CASE("Gg", 1e+6, DIM_KILOGRAM);
            UNIT_CASE("GA", 1e+9, DIM_AMPERE);
            UNIT_CASE("GK", 1e+9, DIM_KILOGRAM);
            UNIT_CASE("Gcd", 1e+9, DIM_CANDELA);
            UNIT_CASE("GN", 1e+9, DIM_NEWTON);
            UNIT_CASE("GJ", 1e+9, DIM_JOULE);
            UNIT_CASE("GPa", 1e+9, DIM_PASCAL);
            UNIT_CASE("GC", 1e+9, DIM_COULOMB);
            UNIT_CASE("GHz", 1e+9, DIM_HERTZ);
            UNIT_CASE("GS", 1e+9, DIM_SIEMENS);
            UNIT_CASE("GOhm", 1e+9, DIM_OHM);
            UNIT_CASE("GF", 1e+9, DIM_FARAD);
            UNIT_CASE("GV", 1e+9, DIM_VOLT);
            UNIT_CASE("GW", 1e+9, DIM_WATT);

            UNIT_CASE("Tm", 1e+12, DIM_METER);
            UNIT_CASE("Ts", 1e+12, DIM_SECOND);
            UNIT_CASE("Tg", 1e+9, DIM_KILOGRAM);
            UNIT_CASE("TA", 1e+12, DIM_AMPERE);
            UNIT_CASE("TK", 1e+12, DIM_KILOGRAM);
            UNIT_CASE("Tcd", 1e+12, DIM_CANDELA);
            UNIT_CASE("TN", 1e+12, DIM_NEWTON);
            UNIT_CASE("TJ", 1e+12, DIM_JOULE);
            UNIT_CASE("TPa", 1e+12, DIM_PASCAL);
            UNIT_CASE("TC", 1e+12, DIM_COULOMB);
            UNIT_CASE("THz", 1e+12, DIM_HERTZ);
            UNIT_CASE("TS", 1e+12, DIM_SIEMENS);
            UNIT_CASE("TOhm", 1e+12, DIM_OHM);
            UNIT_CASE("TF", 1e+12, DIM_FARAD);
            UNIT_CASE("TV", 1e+12, DIM_VOLT);
            UNIT_CASE("TW", 1e+12, DIM_WATT);

            UNIT_CASE("Pm", 1e+15, DIM_METER);
            UNIT_CASE("Ps", 1e+15, DIM_SECOND);
            UNIT_CASE("Pg", 1e+12, DIM_KILOGRAM);
            UNIT_CASE("PA", 1e+15, DIM_AMPERE);
            UNIT_CASE("PK", 1e+15, DIM_KILOGRAM);
            UNIT_CASE("Pcd", 1e+15, DIM_CANDELA);
            UNIT_CASE("PN", 1e+15, DIM_NEWTON);
            UNIT_CASE("PJ", 1e+15, DIM_JOULE);
            UNIT_CASE("PPa", 1e+15, DIM_PASCAL);
            UNIT_CASE("PC", 1e+15, DIM_COULOMB);
            UNIT_CASE("PHz", 1e+15, DIM_HERTZ);
            UNIT_CASE("PS", 1e+15, DIM_SIEMENS);
            UNIT_CASE("POhm", 1e+15, DIM_OHM);
            UNIT_CASE("PF", 1e+15, DIM_FARAD);
            UNIT_CASE("PV", 1e+15, DIM_VOLT);
            UNIT_CASE("PW", 1e+15, DIM_WATT);

            UNIT_CASE("Em", 1e+18, DIM_METER);
            UNIT_CASE("Es", 1e+18, DIM_SECOND);
            UNIT_CASE("Eg", 1e+15, DIM_KILOGRAM);
            UNIT_CASE("EA", 1e+18, DIM_AMPERE);
            UNIT_CASE("EK", 1e+18, DIM_KILOGRAM);
            UNIT_CASE("Ecd", 1e+18, DIM_CANDELA);
            UNIT_CASE("EN", 1e+18, DIM_NEWTON);
            UNIT_CASE("EJ", 1e+18, DIM_JOULE);
            UNIT_CASE("EPa", 1e+18, DIM_PASCAL);
            UNIT_CASE("EC", 1e+18, DIM_COULOMB);
            UNIT_CASE("EHz", 1e+18, DIM_HERTZ);
            UNIT_CASE("ES", 1e+18, DIM_SIEMENS);
            UNIT_CASE("EOhm", 1e+18, DIM_OHM);
            UNIT_CASE("EF", 1e+18, DIM_FARAD);
            UNIT_CASE("EV", 1e+18, DIM_VOLT);
            UNIT_CASE("EW", 1e+18, DIM_WATT);
            default: break;
        }
    }
    if(remaining_length() >= 3) {
        switch(strint(it, 3)) {
            case strint<"mol">(): return advance_with_token(dv::EValue{1.0, { 0, 0, 0, 0, 0, 1, 0 }}, 3);
            default: break;
        }
    }
    if(remaining_length() >= 2) {
        switch(*(std::uint16_t*)it) {
            case strint<"kg">(): return advance_with_token(dv::EValue{1.0, { 0, 0, 1, 0, 0, 0, 0 }}, 2);
            case strint<"cd">(): return advance_with_token(dv::EValue{1.0, { 0, 0, 0, 0, 0, 0, 1 }}, 2);
            case strint<"Pa">(): return advance_with_token(dv::EValue{1.0, { -1, -2, 1, 0, 0, 0, 0 }}, 2);
            case strint<"Hz">(): return advance_with_token(dv::EValue{1.0, { 0, -1, 0, 0, 0, 0, 0 }}, 2);
            
            case strint<"nm">(): return advance_with_token(dv::EValue{1e-9, { 1, 0, 0, 0, 0, 0, 0 }}, 2);
            case strint<"mm">(): return advance_with_token(dv::EValue{1e-3, { 1, 0, 0, 0, 0, 0, 0 }}, 2);
            case strint<"cm">(): return advance_with_token(dv::EValue{1e-2, { 1, 0, 0, 0, 0, 0, 0 }}, 2);
            case strint<"km">(): return advance_with_token(dv::EValue{1e3, { 1, 0, 0, 0, 0, 0, 0 }}, 2);
            
            case strint<"ng">(): return advance_with_token(dv::EValue{1e-12, { 0, 0, 1, 0, 0, 0, 0 }}, 2);
            case strint<"nC">(): return advance_with_token(dv::EValue{1e-9, { 0, 1, 0, 1, 0, 0, 0 }}, 2);
            case strint<"nF">(): return advance_with_token(dv::EValue{1e-9, { 2, -3, 1, -1, 0, 0, 0 }}, 2);
            case strint<"nV">(): return advance_with_token(dv::EValue{1e-9, { 2, -3, 1, -1, 0, 0, 0 }}, 2);
            case strint<"nJ">(): return advance_with_token(dv::EValue{1e-9, { 2, -2, 1, 0, 0, 0, 0 }}, 2);
            case strint<"nN">(): return advance_with_token(dv::EValue{1e-9, { 1, -2, 1, 0, 0, 0, 0 }}, 2);
            case strint<"nA">(): return advance_with_token(dv::EValue{1e-9, { 0, 0, 0, 1, 0, 0, 0 }}, 2);
            case strint<"ns">(): return advance_with_token(dv::EValue{1e-9, { 0, 1, 0, 0, 0, 0, 0 }}, 2);
            
            case strint<"pg">(): return advance_with_token(dv::EValue{1e-15, { 0, 0, 1, 0, 0, 0, 0 }}, 2);
            case strint<"pC">(): return advance_with_token(dv::EValue{1e-12, { 0, 1, 0, 1, 0, 0, 0 }}, 2);
            case strint<"pF">(): return advance_with_token(dv::EValue{1e-12, { 2, -3, 1, -1, 0, 0, 0 }}, 2);
            case strint<"pV">(): return advance_with_token(dv::EValue{1e-12, { 2, -3, 1, -1, 0, 0, 0 }}, 2);
            case strint<"pJ">(): return advance_with_token(dv::EValue{1e-12, { 2, -2, 1, 0, 0, 0, 0 }}, 2);
            case strint<"pN">(): return advance_with_token(dv::EValue{1e-12, { 1, -2, 1, 0, 0, 0, 0 }}, 2);
            case strint<"pA">(): return advance_with_token(dv::EValue{1e-12, { 0, 0, 0, 1, 0, 0, 0 }}, 2);
            case strint<"ps">(): return advance_with_token(dv::EValue{1e-12, { 0, 1, 0, 0, 0, 0, 0 }}, 2);
           
            case strint<"mg">(): return advance_with_token(dv::EValue{1e-6, { 1, 0, 0, 0, 0, 0, 0 }}, 2);
            case strint<"ms">(): return advance_with_token(dv::EValue{1e-3, { 0, 1, 0, 0, 0, 0, 0 }}, 2);
            default: break;
        }
    }
    if(remaining_length() >= 1){
        switch(*(std::uint8_t*)it) {
            case strint<"g">(): return advance_with_token(dv::EValue{1e-3, { 0, 0, 1, 0, 0, 0, 0 }}, 2);
            case strint<"m">(): return advance_with_token(dv::EValue{1.0, { 1, 0, 0, 0, 0, 0, 0 }}, 1);
            case strint<"s">(): return advance_with_token(dv::EValue{1.0, { 0, 1, 0, 0, 0, 0, 0 }}, 1);
            case strint<"A">(): return advance_with_token(dv::EValue{1.0, { 0, 0, 0, 1, 0, 0, 0 }}, 1);
            case strint<"K">(): return advance_with_token(dv::EValue{1.0, { 0, 0, 0, 0, 1, 0, 0 }}, 1);
            case strint<"N">(): return advance_with_token(dv::EValue{1.0, { 1, -2, 1, 0, 0, 0, 0 }}, 1);
            case strint<"J">(): return advance_with_token(dv::EValue{1.0, { 2, -2, 1, 0, 0, 0, 0 }}, 1);
            case strint<"C">(): return advance_with_token(dv::EValue{1.0, { 0, 1, 0, 1, 0, 0, 0 }}, 1);
            case strint<"F">(): return advance_with_token(dv::EValue{1.0, { -2, 4, -1, 2, 0, 0, 0 }}, 1);
            case strint<"V">(): return advance_with_token(dv::EValue{1.0, { 2, -3, 1, -1, 0, 0, 0 }}, 1);
            default: break;
        }
    }
    return {};
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