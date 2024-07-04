#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const string& source) : source(source), currentIndex(0), currentChar(source[0]) {}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        if (isalpha(currentChar)) {
            tokens.push_back(lexIdentifier());
        } else if (isdigit(currentChar)) {
            tokens.push_back(lexNumber());
        } else {
            tokens.push_back(lexOperator());
        }
    }
    return tokens;
}

char Lexer::advance() {
    currentChar = source[++currentIndex];
    return currentChar;
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return source[currentIndex + 1];
}

bool Lexer::isAtEnd() {
    return currentIndex >= source.length();
}

void Lexer::skipWhitespace() {
    while (isspace(currentChar) && !isAtEnd()) {
        advance();
    }
}

Token Lexer::lexIdentifier() {
    string value;
    while (isalnum(currentChar) && !isAtEnd()) {
        value += currentChar;
        advance();
    }
    return Token(TokenType::IDENTIFIER, value);
}

Token Lexer::lexNumber() {
    string value;
    while (isdigit(currentChar) && !isAtEnd()) {
        value += currentChar;
        advance();
    }
    return Token(TokenType::NUMBER, value);
}

Token Lexer::lexOperator() {
    char op = currentChar;
    advance();
    return Token(TokenType::OPERATOR, string(1, op));
}

