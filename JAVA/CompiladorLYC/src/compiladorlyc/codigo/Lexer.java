package compiladorlyc.codigo;

import java.util.ArrayList;
import java.util.List;

public class Lexer {
    private final String source;
    private int current;

    public Lexer(String source) {
        this.source = source;
        this.current = 0;
    }

    public List<Token> tokenize() {
        List<Token> tokens = new ArrayList<>();
        while (!isAtEnd()) {
            skipWhitespace();
            if (isAtEnd()) break; // Asegurarse de no avanzar más si se alcanza el final
            char c = advance();
            if (Character.isDigit(c)) {
                tokens.add(lexNumber());
            } else if (Character.isLetter(c)) {
                tokens.add(lexIdentifier());
            } else if ("+-*/=><".indexOf(c) >= 0) {
                tokens.add(lexOperator());
            } else if (c == ';') {
                tokens.add(lexSemicolon());
            } else {
                tokens.add(new Token(TokenType.UNKNOWN, String.valueOf(c)));
            }
        }
        tokens.add(new Token(TokenType.END_OF_FILE, ""));
        return tokens;
    }

    private boolean isAtEnd() {
        return current >= source.length();
    }

    private char advance() {
        if (!isAtEnd()) {
            return source.charAt(current++);
        }
        return '\0'; // Retorna un carácter nulo si ya está al final para evitar excepciones
    }

    private char peek() {
        if (isAtEnd()) return '\0';
        return source.charAt(current);
    }

    private Token lexNumber() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));
        while (Character.isDigit(peek()) || peek() == '.') {
            value.append(advance());
        }
        if (value.toString().contains(".")) {
            return new Token(TokenType.FLOAT, value.toString());
        } else {
            return new Token(TokenType.INTEGER, value.toString());
        }
    }

    private Token lexIdentifier() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));
        while (Character.isLetterOrDigit(peek())) {
            value.append(advance());
        }
        return new Token(TokenType.IDENTIFIER, value.toString());
    }

    private Token lexOperator() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));
        if ((value.toString().equals("=") || value.toString().equals(">") || value.toString().equals("<")) && peek() == '=') {
            value.append(advance());
        }
        return new Token(TokenType.OPERATOR, value.toString());
    }

    private Token lexSemicolon() {
        return new Token(TokenType.SEMICOLON, ";");
    }

    private void skipWhitespace() {
        while (!isAtEnd() && Character.isWhitespace(peek())) {
            advance();
        }
    }
}