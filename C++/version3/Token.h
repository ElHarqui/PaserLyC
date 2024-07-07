#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

// Enum para los tipos de tokens que nuestro lexer reconocerá.
enum class TokenType {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    UNKNOWN
};

// Clase Token que representa un token en nuestro lenguaje.
class Token {
public:
    TokenType type; // El tipo del token.
    string value; // El valor del token.

    // Constructor para inicializar el token con un tipo y un valor.
    Token(TokenType type, const string& value) : type(type), value(value) {}
};

#endif

