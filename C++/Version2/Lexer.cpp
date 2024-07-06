#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const string& source) : source(source), pos(0) {}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        char currentChar = peek();
        if (isdigit(currentChar)) {
            tokens.push_back(lexNumber());
        } else if (isalpha(currentChar)) {
            tokens.push_back(lexIdentifier());
        } else {
            tokens.push_back(lexOperator());
        }
    }
    tokens.push_back({TokenType::END, ""});
    return tokens;
}

char Lexer::peek() const {
    return source[pos];
}

char Lexer::advance() {
    return source[pos++];
}

bool Lexer::isAtEnd() const {
    return pos >= source.size();
}

Token Lexer::lexNumber() {
    string value;
    while (!isAtEnd() && isdigit(peek())) {
        value += advance();
    }
    return {TokenType::NUMBER, value};
}

Token Lexer::lexIdentifier() {
    string value;
    while (!isAtEnd() && (isalnum(peek()) || peek() == '_')) {
        value += advance();
    }
    if (value == "int" || value == "return" || value == "if" || value == "else") { // Palabras reservadas
        return {TokenType::KEYWORD, value};
    }
    return {TokenType::IDENTIFIER, value};
}

Token Lexer::lexOperator() {
    char currentChar = advance();
    switch (currentChar) {
        case '(': case ')':
        case '+': case '-':
        case '*': case '/':
        case '=': case ';':
        case '>': case '<':
            return {TokenType::OPERATOR, string(1, currentChar)};
        case '!':
            if (!isAtEnd() && peek() == '=') {
                advance();
                return {TokenType::OPERATOR, "!="};
            }
            break;
        case '>':
            if (!isAtEnd() && peek() == '=') {
                advance();
                return {TokenType::OPERATOR, ">="};
            }
            break;
        case '<':
            if (!isAtEnd() && peek() == '=') {
                advance();
                return {TokenType::OPERATOR, "<="};
            }
            break;
    }
    return {TokenType::UNKNOWN, string(1, currentChar)};
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && isspace(peek())) {
        advance();
    }
}

