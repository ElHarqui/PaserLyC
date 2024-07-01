#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

// Enumeración para los tipos de tokens
enum class TokenType {
    IDENTIFIER, // Identificadores (variables, funciones, etc.)
    KEYWORD,    // Palabras clave (if, else, while, return, etc.)
    NUMBER,     // Números (enteros)
    OPERATOR,   // Operadores ( +, -, *, /, etc.)
    END         // Fin del archivo
};

// Estructura para representar un token
struct Token {
    TokenType type;    // Tipo del token
    string value; // Valor del token
};

// Clase Lexer para el análisis léxico
class Lexer {
public:
    // Constructor que toma el código fuente como entrada
    Lexer(const string& source) : source(source), pos(0) {}

    // Método para tokenizar el código fuente
    vector<Token> tokenize() {
        vector<Token> tokens;
        while (pos < source.length()) {
            if (isspace(source[pos])) {
                ++pos;
                continue;
            }

            if (isalpha(source[pos])) {
                tokens.push_back(lexIdentifier());
            } else if (isdigit(source[pos])) {
                tokens.push_back(lexNumber());
            } else if (ispunct(source[pos])) {
                tokens.push_back(lexOperator());
            } else {
                ++pos;  // Ignorar caracteres desconocidos
            }
        }
        tokens.push_back({TokenType::END, ""}); // Agregar token de fin
        return tokens;
    }

private:
    string source; // Código fuente
    size_t pos;         // Posición actual en el código fuente

    // Método para reconocer identificadores y palabras clave
    Token lexIdentifier() {
        size_t start = pos;
        while (pos < source.length() && isalnum(source[pos])) {
            ++pos;
        }
        string value = source.substr(start, pos - start);
        if (keywords.find(value) != keywords.end()) {
            return {TokenType::KEYWORD, value};
        }
        return {TokenType::IDENTIFIER, value};
    }

    // Método para reconocer números
    Token lexNumber() {
        size_t start = pos;
        while (pos < source.length() && isdigit(source[pos])) {
            ++pos;
        }
        string value = source.substr(start, pos - start);
        return {TokenType::NUMBER, value};
    }

    // Método para reconocer operadores
    Token lexOperator() {
        string value(1, source[pos++]);
        return {TokenType::OPERATOR, value};
    }

    // Mapa de palabras clave
    unordered_map<string, TokenType> keywords = {
        {"if", TokenType::KEYWORD},
        {"else", TokenType::KEYWORD},
        {"while", TokenType::KEYWORD},
        {"return", TokenType::KEYWORD}
    };
};

// Clase Parser para el análisis sintáctico
class Parser {
public:
    // Constructor que toma los tokens como entrada
    Parser(const vector<Token>& tokens) : tokens(tokens), pos(0) {}

    // Método para iniciar el análisis sintáctico
    void parse() {
        while (pos < tokens.size() && tokens[pos].type != TokenType::END) {
            if (tokens[pos].type == TokenType::KEYWORD && tokens[pos].value == "return") {
                parseReturnStatement();
            } else {
                parseExpression();
            }
        }
    }

private:
    vector<Token> tokens; // Lista de tokens
    size_t pos;                // Posición actual en la lista de tokens

    // Método para analizar una sentencia return
    void parseReturnStatement() {
        ++pos;  // Consumir 'return'
        parseExpression();
        if (tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == ";") {
            ++pos;  // Consumir ';'
        } else {
            cerr << "Error: Expected ';' after return statement" << endl;
        }
    }

    // Método para analizar una expresión
    void parseExpression() {
        if (tokens[pos].type == TokenType::NUMBER || tokens[pos].type == TokenType::IDENTIFIER) {
            ++pos;  // Consumir número o identificador
        } else {
            cerr << "Error: Expected expression" << endl;
        }
    }
};

// Función principal
int main() {
    // Código fuente de ejemplo
    string source = "int main() { return 0; }";
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();

    // Imprimir tokens
    cout << "Tokens:" << endl;
    for (const Token& token : tokens) {
        cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value << endl;
    }

    // Parsear los tokens
    Parser parser(tokens);
    parser.parse();

    return 0;
}

