
package compiladorlyc.codigo;

enum TokenType {
    INTEGER, FLOAT, IDENTIFIER, OPERATOR, SEMICOLON, END_OF_FILE, UNKNOWN
}

public class Token {
    TokenType type;
    String value;

    Token(TokenType type, String value) {
        this.type = type;
        this.value = value;
    }
}

