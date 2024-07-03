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
    Lexer(const string& source) : source(source), start(0), current(0) {}

    // Función que convierte el código fuente en tokens.
    vector<Token> tokenize();

private:
    string source; // El código fuente.
    size_t start; // El inicio del lexema actual.
    size_t current; // La posición actual en el código fuente.

    // Función que analiza el siguiente token.
    Token lexToken();
    
    // Función que analiza un identificador o palabra clave.
    Token lexIdentifier();

    // Función que analiza un número.
    Token lexNumber();

    // Función que analiza un operador.
    Token lexOperator();

    // Función que salta los espacios en blanco.
    void skipWhitespace();

    // Función que verifica si hemos llegado al final del código fuente.
    bool isAtEnd() const;

    // Función que obtiene el carácter actual.
    char advance();

    // Función que obtiene el carácter actual sin avanzar.
    char peek() const;

    // Función que obtiene el siguiente carácter sin avanzar.
    char peekNext() const;
};

#endif

