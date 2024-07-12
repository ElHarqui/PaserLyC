package prueba;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Parser {

    private final List<Token> tokens;
    private int current;
    private Map<String, TokenType> symbolTable = new HashMap<>();

    public Parser(List<Token> tokens) {
        this.tokens = tokens;
        this.current = 0;
    }

    public ASTNode parse() {
        try {
            return program();
        } catch (ParseError e) {
            System.err.println(e.getMessage());
            return null;
        }
    }

    private ASTNode program() {
        ASTNode root = statement();
        while (!isAtEnd()) {
            root = new ASTNode(TokenType.SEMICOLON, ";", root, statement());
        }
        return root;
    }

    private boolean isAtEnd() {
        return current >= tokens.size() || tokens.get(current).tipo == TokenType.END_OF_FILE;
    }

    private Token advance() {
        if (!isAtEnd()) {
            current++;
        }
        return tokens.get(current - 1);
    }

    private Token peek() {
        if (isAtEnd()) {
            return tokens.get(tokens.size() - 1);
        }
        return tokens.get(current);
    }

    private Token expect(TokenType type, String message) {
        if (peek().tipo == type) {
            return advance();
        }
        throw new ParseError(message);
    }

    private ASTNode factor() {
        if (!isAtEnd() && (peek().tipo == TokenType.INTEGER || peek().tipo == TokenType.FLOAT || peek().tipo == TokenType.IDENTIFIER || peek().tipo == TokenType.STRING)) {
            Token token = advance();
            return new ASTNode(token.tipo, token.valor);
        } else if (!isAtEnd() && peek().tipo == TokenType.DELIMITER && peek().valor.equals("(")) {
            advance(); // Consume '('
            ASTNode node = expression();
            expect(TokenType.DELIMITER, "Se esperaba ')'");
            return node;
        } else {
            throw new ParseError("Error: Se esperaba un factor válido");
        }
    }

    private ASTNode expression() {
        ASTNode node = term();
        while (!isAtEnd() && peek().tipo == TokenType.OPERATOR && (peek().valor.equals("+") || peek().valor.equals("-"))) {
            Token token = advance();
            ASTNode newNode = new ASTNode(token.tipo, token.valor);
            newNode.left = node;
            newNode.right = term();
            node = newNode;
        }
        return node;
    }

    private ASTNode term() {
        ASTNode node = factor();
        while (!isAtEnd() && peek().tipo == TokenType.OPERATOR && (peek().valor.equals("*") || peek().valor.equals("/"))) {
            Token token = advance();
            ASTNode newNode = new ASTNode(token.tipo, token.valor);
            newNode.left = node;
            newNode.right = factor();
            if (token.valor.equals("/") && newNode.right.value.equals("0")) {
                throw new ParseError("Error: División por cero detectada");
            }
            node = newNode;
        }
        return node;
    }

    private ASTNode statement() {
        if (peek().tipo == TokenType.KEYWORD) {
            return declaration();
        } else if (peek().tipo == TokenType.OUTPUT) {
            return handleCoutStatement();
        } else if (peek().tipo == TokenType.IDENTIFIER) {
            return assignment();
        } else {
            return expressionStatement();
        }
    }

    private ASTNode declaration() {
        Token keyword = expect(TokenType.KEYWORD, "Error: Se esperaba una palabra clave de tipo de dato");
        Token identifier = expect(TokenType.IDENTIFIER, "Error: Se esperaba un identificador después del tipo de dato");
        expect(TokenType.OPERATOR, "Error: Se esperaba '=' después del identificador");
        ASTNode value = expression();
        expect(TokenType.SEMICOLON, "Error: Se esperaba ';' después de la declaración de la variable");
        return new ASTNode(TokenType.DATA_TYPE, keyword.valor, new ASTNode(TokenType.IDENTIFIER, identifier.valor), value);
    }

    private ASTNode assignment() {
        Token identifier = expect(TokenType.IDENTIFIER, "Error: Se esperaba un identificador para la asignación");
        expect(TokenType.OPERATOR, "Error: Se esperaba '=' para la asignación");
        ASTNode value = expression();
        expect(TokenType.SEMICOLON, "Error: Se esperaba ';' después de la asignación");
        return new ASTNode(TokenType.OPERATOR, "=", new ASTNode(TokenType.IDENTIFIER, identifier.valor), value);
    }

    private ASTNode expressionStatement() {
        ASTNode expr = expression();
        expect(TokenType.SEMICOLON, "Error: Se esperaba ';' después de la expresión");
        return expr;
    }

    private ASTNode handleCoutStatement() {
        expect(TokenType.OUTPUT, "Error: Se esperaba 'cout'");
        expect(TokenType.SHIFT_LEFT, "Error: Se esperaba '<<'");
        ASTNode expr = expression();
        expect(TokenType.SEMICOLON, "Error: Se esperaba ';' después de 'cout <<'");
        return new ASTNode(TokenType.OUTPUT, "cout <<", expr);
    }
    public int getcurrent(){
        return current;
    }
}
