#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source), current(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        tokens.push_back(lexToken());
    }
    tokens.push_back(Token(TokenType::END_OF_FILE, ""));
    return tokens;
}

char Lexer::advance() {
    return source[current++];
}

char Lexer::peek() const {
    return source[current];
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek())) {
        advance();
    }
}

Token Lexer::lexToken() {
    if (std::isalpha(peek())) return lexIdentifier();
    if (std::isdigit(peek())) return lexNumber();
    if (std::ispunct(peek())) return lexOperator();
    return Token(TokenType::UNKNOWN, std::string(1, advance()));
}

Token Lexer::lexIdentifier() {
    std::string value;
    while (!isAtEnd() && std::isalnum(peek())) {
        value += advance();
    }
    if (value == "int" || value == "float") {
        return Token(TokenType::KEYWORD, value);
    }
    return Token(TokenType::IDENTIFIER, value);
}

Token Lexer::lexNumber() {
    std::string value;
    while (!isAtEnd() && std::isdigit(peek())) {
        value += advance();
    }
    return Token(TokenType::NUMBER, value);
}

Token Lexer::lexOperator() {
    char currentChar = advance();
    switch (currentChar) {
        case '+': case '-': case '*': case '/': case '=': case ';':
            return Token(TokenType::OPERATOR, std::string(1, currentChar));
        default:
            return Token(TokenType::UNKNOWN, std::string(1, currentChar));
    }
}

