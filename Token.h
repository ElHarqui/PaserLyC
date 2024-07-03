#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

// Definición de los tipos de tokens que nuestro lexer reconocerá.
enum class TokenType {
    KEYWORD, // int, float, etc.
    IDENTIFIER, // a, b, c, etc.
    NUMBER, // 4, 5, 0, etc.
    OPERATOR, // +, -, *, /, etc.
    SEMICOLON, // ;
    EOF // End of file
};



// Clase Token que representa un token en nuestro lenguaje.
class Token {
public:
    TokenType type; // El tipo del token.
    string value; // El valor del token.

    // Constructor para inicializar un token.
    Token(TokenType type, const string& value) : type(type), value(value) {}
};



#endif

