package prueba;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Lexer {

    private final String source;
    private int current;

    private static final Map<String, TokenType> keywords = new HashMap<>();

    static {
        keywords.put("int", TokenType.KEYWORD);
        keywords.put("float", TokenType.KEYWORD);
        keywords.put("double", TokenType.KEYWORD);
        keywords.put("char", TokenType.KEYWORD);
        keywords.put("bool", TokenType.KEYWORD);
        keywords.put("string", TokenType.KEYWORD);
        keywords.put("if", TokenType.CONDITIONAL);
        keywords.put("else", TokenType.CONDITIONAL);
        keywords.put("for", TokenType.FOR);
        keywords.put("while", TokenType.LOOP);
        keywords.put("++", TokenType.INCREMENT);
        keywords.put("<<", TokenType.SHIFT_LEFT);
        keywords.put(">>", TokenType.SHIFT_RIGHT);
        keywords.put("cout", TokenType.OUTPUT);
        keywords.put("cin", TokenType.INPUT);
        keywords.put("\"", TokenType.DOUBLE_QUOTE);
    }

    public Lexer(String source) {
        this.source = source;
        this.current = 0;
    }

    public List<Token> tokenize() {
        List<Token> tokens = new ArrayList<>();
        while (!isAtEnd()) {
            skipWhitespace();
            if (isAtEnd()) {
                break;
            }
            char c = advance();
            if (Character.isDigit(c)) {
                tokens.add(lexNumber());
            } else if (Character.isLetter(c)) {
                tokens.add(lexIdentifierOrKeyword());
            } else if ("+-*/=><!".indexOf(c) >= 0) {
                tokens.add(lexOperator());
            } else if (c == ';') {
                tokens.add(new Token(TokenType.SEMICOLON, ";"));
            } else if (c == '(' || c == ')') {
                tokens.add(new Token(TokenType.DELIMITER, String.valueOf(c)));
            } else if (c == '{' || c == '}') {
                tokens.add(new Token(TokenType.DELIMITER, String.valueOf(c)));
            } else if (c == '"') {
                tokens.add(lexString());
            } else if (c == '#') {
                tokens.add(lexPreprocessorDirective());
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
        if (isAtEnd()) {
            return '\0';
        }
        return source.charAt(current);
    }

    private Token lexNumber() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));
        while (!isAtEnd() && (Character.isDigit(peek()) || peek() == '.')) {
            value.append(advance());
        }
        if (value.toString().contains(".")) {
            return new Token(TokenType.FLOAT, value.toString());
        } else {
            return new Token(TokenType.INTEGER, value.toString());
        }
    }

    private Token lexIdentifierOrKeyword() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));
        while (!isAtEnd() && Character.isLetterOrDigit(peek())) {
            value.append(advance());
        }
        String identifier = value.toString();
        TokenType type = keywords.getOrDefault(identifier, TokenType.IDENTIFIER);
        return new Token(type, identifier);
    }

    private Token lexOperator() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));

        while (!isAtEnd()) {
            String combined = value.toString() + peek();
            if (keywords.containsKey(combined)) {
                value.append(advance());
            } else {
                break;
            }
        }

        TokenType type = keywords.getOrDefault(value.toString(), TokenType.OPERATOR);
        return new Token(type, value.toString());
    }

    private Token lexString() {
        StringBuilder value = new StringBuilder();
        while (!isAtEnd() && peek() != '"') {
            value.append(advance());
        }
        if (!isAtEnd()) {
            advance();
        }
        return new Token(TokenType.STRING, value.toString());
    }

    private Token lexPreprocessorDirective() {
        StringBuilder value = new StringBuilder();
        value.append(source.charAt(current - 1));
        while (!isAtEnd() && peek() != '\n') {
            value.append(advance());
        }
        return new Token(TokenType.PREPROCESSOR, value.toString());
    }

    private void skipWhitespace() {
        while (!isAtEnd() && Character.isWhitespace(peek())) {
            advance();
        }
    }
}
