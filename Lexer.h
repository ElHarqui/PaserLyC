#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>
using namespace std;

class Lexer {
public:
    Lexer(const string& source);
    vector<Token> tokenize();

private:
    string source;
    size_t currentIndex;
    char currentChar;

    char advance();
    char peek();
    bool isAtEnd();
    void skipWhitespace();

    Token lexIdentifier();
    Token lexNumber();
    Token lexOperator();
};

#endif // LEXER_H

