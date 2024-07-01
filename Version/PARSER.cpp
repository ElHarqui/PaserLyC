#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

// Enumeraci�n para los tipos de tokens
enum class TokenType {
    IDENTIFIER, // Identificadores (variables, funciones, etc.)
    KEYWORD,    // Palabras clave (if, else, while, return, etc.)
    NUMBER,     // N�meros (enteros)
    OPERATOR,   // Operadores ( +, -, *, /, etc.)
    END         // Fin del archivo
};

// Estructura para representar un token
struct Token {
    TokenType type;    // Tipo del token
    string value; // Valor del token
};

// Clase Lexer para el an�lisis l�xico
class Lexer {
public:
    // Constructor que toma el c�digo fuente como entrada
    Lexer(const string& source) : source(source), pos(0) {}

    // M�todo para tokenizar el c�digo fuente
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
    string source; // C�digo fuente
    size_t pos;         // Posici�n actual en el c�digo fuente

    // M�todo para reconocer identificadores y palabras clave
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

    // M�todo para reconocer n�meros
    Token lexNumber() {
        size_t start = pos;
        while (pos < source.length() && isdigit(source[pos])) {
            ++pos;
        }
        string value = source.substr(start, pos - start);
        return {TokenType::NUMBER, value};
    }

    // M�todo para reconocer operadores
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

// Clase Parser para el an�lisis sint�ctico
class Parser {
public:
    // Constructor que toma los tokens como entrada
    Parser(const vector<Token>& tokens) : tokens(tokens), pos(0) {}

    // M�todo para iniciar el an�lisis sint�ctico
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
    size_t pos;                // Posici�n actual en la lista de tokens

    // M�todo para analizar una sentencia return
    void parseReturnStatement() {
        ++pos;  // Consumir 'return'
        parseExpression();
        if (tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == ";") {
            ++pos;  // Consumir ';'
        } else {
            cerr << "Error: Expected ';' after return statement" << endl;
        }
    }

    // M�todo para analizar una expresi�n
    void parseExpression() {
        if (tokens[pos].type == TokenType::NUMBER || tokens[pos].type == TokenType::IDENTIFIER) {
            ++pos;  // Consumir n�mero o identificador
        } else {
            cerr << "Error: Expected expression" << endl;
        }
    }
};

// Funci�n principal
int main() {
    // C�digo fuente de ejemplo
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

