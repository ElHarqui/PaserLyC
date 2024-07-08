package compiladorlyc.codigo;

import java.util.List;

public class Parser {
    private final List<Token> tokens;
    private int current;

    public Parser(List<Token> tokens) {
        this.tokens = tokens;
        this.current = 0;
    }

    public ASTNode parse() {
        try {
            return statement();
        } catch (ParseError e) {
            System.err.println(e.getMessage());
            return null; // En caso de error, retorna null
        }
    }

    private boolean isAtEnd() {
        return current >= tokens.size() || tokens.get(current).type == TokenType.END_OF_FILE;
    }

    private Token advance() {
        if (!isAtEnd()) current++;
        return tokens.get(current - 1);
    }

    private Token peek() {
        if (isAtEnd()) return tokens.get(tokens.size() - 1);
        return tokens.get(current);
    }

    private Token expect(TokenType type, String message) {
        if (peek().type == type) return advance();
        throw new ParseError(message);
    }

    private ASTNode statement() {
        ASTNode expr = expression();
        expect(TokenType.SEMICOLON, "Error: 1Expected ';' after expression");
        return expr;
    }

    private ASTNode expression() {
        ASTNode node = term();
        while (peek().type == TokenType.OPERATOR && (peek().value.equals("+") || peek().value.equals("-"))) {
            Token token = advance();
            ASTNode newNode = new ASTNode(token.type, token.value);
            newNode.left = node;
            newNode.right = term();
            node = newNode;
        }
        return node;
    }

    private ASTNode term() {
        ASTNode node = factor();
        while (peek().type == TokenType.OPERATOR && (peek().value.equals("*") || peek().value.equals("/"))) {
            Token token = advance();
            ASTNode newNode = new ASTNode(token.type, token.value);
            newNode.left = node;
            newNode.right = factor();
            if (token.value.equals("/") && newNode.right.value.equals("0")) {
                throw new ParseError("Error: Division by zero detected");
            }
            node = newNode;
        }
        return node;
    }

    private ASTNode factor() {
        if (peek().type == TokenType.INTEGER || peek().type == TokenType.FLOAT || peek().type == TokenType.IDENTIFIER) {
            return new ASTNode(advance().type, advance().value);
        } else if (peek().type == TokenType.OPERATOR && peek().value.equals("(")) {
            advance();
            ASTNode node = expression();
            expect(TokenType.OPERATOR, "Error: Expected ')' after expression");
            return node;
        }
        throw new ParseError("Error: Expected expression");
    }
}
