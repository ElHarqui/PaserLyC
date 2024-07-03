#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t current;

    char advance();
    char peek() const;
    bool isAtEnd() const;
    void skipWhitespace();

    Token lexToken();
    Token lexIdentifier();
    Token lexNumber();
    Token lexOperator();
};

#endif

