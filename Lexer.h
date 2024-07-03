#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

// La clase Lexer es responsable de convertir el c�digo fuente en una serie de tokens.
class Lexer {
public:
    // Constructor que inicializa el lexer con el c�digo fuente.
    Lexer(const string& source) : source(source), start(0), current(0) {}

    // Funci�n que convierte el c�digo fuente en tokens.
    vector<Token> tokenize();

private:
    string source; // El c�digo fuente.
    size_t start; // El inicio del lexema actual.
    size_t current; // La posici�n actual en el c�digo fuente.

    // Funci�n que analiza el siguiente token.
    Token lexToken();
    
    // Funci�n que analiza un identificador o palabra clave.
    Token lexIdentifier();

    // Funci�n que analiza un n�mero.
    Token lexNumber();

    // Funci�n que analiza un operador.
    Token lexOperator();

    // Funci�n que salta los espacios en blanco.
    void skipWhitespace();

    // Funci�n que verifica si hemos llegado al final del c�digo fuente.
    bool isAtEnd() const;

    // Funci�n que obtiene el car�cter actual.
    char advance();

    // Funci�n que obtiene el car�cter actual sin avanzar.
    char peek() const;

    // Funci�n que obtiene el siguiente car�cter sin avanzar.
    char peekNext() const;
};

#endif

