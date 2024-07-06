#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    OPERATOR,
    END
};

struct Token {
    TokenType type;
    string value;
};

#endif // TOKEN_H

