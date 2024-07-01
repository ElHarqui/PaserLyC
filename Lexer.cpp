#include "Lexer.h"

Lexer::Lexer(const string& source) : source(source), pos(0) {
    keywords = {
        {"if", TokenType::KEYWORD},
        {"else", TokenType::KEYWORD},
        {"while", TokenType::KEYWORD},
        {"return", TokenType::KEYWORD}
    };
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (pos < source.length()) {
        if (isspace(source[pos])) {
            ++pos;
            continue;
        }

        if (isalpha(source[pos])) {
            tokens.push_back(lexIdentifier());
        } else if (isdigit(source[pos])) {
            tokens.push_back(lexNumber());
        } else if (ispunct(source[pos])) {
            tokens.push_back(lexOperator());
        } else {
            ++pos;  // Ignorar caracteres desconocidos
        }
    }
    tokens.push_back({TokenType::END, ""}); // Agregar token de fin
    return tokens;
}

Token Lexer::lexIdentifier() {
    size_t start = pos;
    while (pos < source.length() && isalnum(source[pos])) {
        ++pos;
    }
    string value = source.substr(start, pos - start);
    if (keywords.find(value) != keywords.end()) {
        return {TokenType::KEYWORD, value};
    }
    return {TokenType::IDENTIFIER, value};
}

Token Lexer::lexNumber() {
    size_t start = pos;
    while (pos < source.length() && isdigit(source[pos])) {
        ++pos;
    }
    string value = source.substr(start, pos - start);
    return {TokenType::NUMBER, value};
}

Token Lexer::lexOperator() {
    string value(1, source[pos++]);
    return {TokenType::OPERATOR, value};
}

