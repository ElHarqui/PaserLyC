#include "Lexer.h"
#include <cctype>

using namespace std;

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (!isAtEnd()) {
        start = current;
        Token token = lexToken();
        if (token.type != TokenType::UNKNOWN) {
            tokens.push_back(token);
        }
    }
    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}


Token Lexer::lexToken() {
    skipWhitespace();
    if (isAtEnd()) return {TokenType::END_OF_FILE, ""};

    char c = advance();

    if (isalpha(c)) return lexIdentifier();
    if (isdigit(c)) return lexNumber();
    if (ispunct(c)) return lexOperator();

    return {TokenType::UNKNOWN, string(1, c)};
}

Token Lexer::lexIdentifier() {
    while (isalnum(peek())) advance();
    string value = source.substr(start, current - start);

    if (value == "int" || value == "float") {
        return {TokenType::KEYWORD, value};
    }

    return {TokenType::IDENTIFIER, value};
}

Token Lexer::lexNumber() {
    while (isdigit(peek())) advance();
    return {TokenType::NUMBER, source.substr(start, current - start)};
}

Token Lexer::lexOperator() {
    char c = source[start];
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '<':
        case '>':
            return {TokenType::OPERATOR, string(1, c)};
        default:
            return {TokenType::UNKNOWN, string(1, c)};
    }
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && isspace(peek())) {
        advance();
    }
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

char Lexer::advance() {
    return source[current++];
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() const {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

