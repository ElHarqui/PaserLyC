#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class TokenType {
    UNKNOWN,
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    SEPARATOR,
    NUMBER
};

struct Token {
    TokenType type;
    string value;

    Token(TokenType t, string v) : type(t), value(v) {}
};

#endif // TOKEN_H

