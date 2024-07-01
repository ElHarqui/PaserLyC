#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include "Token.h"

using namespace std;

class Lexer {
public:
    Lexer(const string& source);
    vector<Token> tokenize();

private:
    string source;
    size_t pos;
    unordered_map<string, TokenType> keywords;

    Token lexIdentifier();
    Token lexNumber();
    Token lexOperator();
};

#endif // LEXER_H

