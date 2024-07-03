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
    char advance();
    char peek() const;
    bool isAtEnd() const;
    Token lexToken();
    Token lexIdentifier();
    Token lexNumber();
    Token lexOperator();
    void skipWhitespace();

    std::string source;
    size_t current;
};

#endif

