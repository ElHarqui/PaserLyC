#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER, 
	NUMBER, OPERATOR, 
	KEYWORD, 
	END_OF_FILE, 
	UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    Token(TokenType type, const std::string& value) : type(type), value(value) {}
};

#endif

