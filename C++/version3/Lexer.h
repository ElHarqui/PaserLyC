#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

// La clase Lexer es responsable de convertir el código fuente en una serie de tokens.
class Lexer {
public:
    // Constructor que inicializa el lexer con el código fuente.
    Lexer(const string& source);

    // Función para tokenizar todo el código fuente.
    // Devuelve un vector de objetos Token que representan los tokens en el código fuente.
    vector<Token> tokenize();

private:
    string source; // El código fuente a tokenizar.
    size_t current; // La posición actual en el código fuente.

    // Avanza la posición actual y devuelve el carácter actual.
    char advance();

    // Mira el carácter actual sin avanzar la posición.
    char peek() const;

    // Verifica si el lexer ha llegado al final del código fuente.
    bool isAtEnd() const;

    // Omite los caracteres de espacio en blanco en el código fuente.
    void skipWhitespace();

    // Lexea un solo token del código fuente.
    // Devuelve un objeto Token que representa el token lexeado.
    Token lexToken();

    // Lexea un token identificador del código fuente.
    // Devuelve un objeto Token que representa el identificador.
    Token lexIdentifier();

    // Lexea un token de número del código fuente.
    // Devuelve un objeto Token que representa el número.
    Token lexNumber();

    // Lexea un token de operador del código fuente.
    // Devuelve un objeto Token que representa el operador.
    Token lexOperator();
};

#endif

