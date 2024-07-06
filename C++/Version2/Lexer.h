#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class Lexer {
public:
    Lexer(const string& source);
    vector<Token> tokenize();

private:
    string source;
    size_t pos;

    char peek() const;
    char advance();
    bool isAtEnd() const;
    Token lexNumber();
    Token lexIdentifier();
    Token lexOperator();
    void skipWhitespace();
};

#endif // LEXER_H

