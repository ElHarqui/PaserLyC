
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
public int getcurrent(){
    return current;
}
    public ASTNode parse() {
        try {
            return statement();
        } catch (ParseError e) {
            System.err.println(e.getMessage());
            return null;
        }
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

    private void declareVariable(Token token) {
        if (symbolTable.containsKey(token.valor)) {
            throw new ParseError("Error: Variable '" + token.valor + "' ya declarada");
        }
        symbolTable.put(token.valor, token.tipo);
    }

    private boolean isVariableDeclared(Token token) {
        return symbolTable.containsKey(token.valor);
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
    if (!isAtEnd() && (peek().tipo == TokenType.INTEGER || peek().tipo == TokenType.FLOAT || peek().tipo == TokenType.IDENTIFIER || peek().tipo == TokenType.DATA_TYPE)) {
        Token token = advance();
        if (token.tipo == TokenType.IDENTIFIER) {
            if (!isVariableDeclared(token)) {
                throw new ParseError("Error: Variable '" + token.valor + "' no declarada");
            }
        }
        return new ASTNode(token.tipo, token.valor);
    } else if (!isAtEnd() && peek().tipo == TokenType.OPERATOR && peek().valor.equals("(")) {
        advance();
        ASTNode node = expression();
        expect(TokenType.OPERATOR, ")");
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
        if (peek().tipo == TokenType.OUTPUT) {
            return printStatement();
        } else {
            ASTNode expr = expression();
            if (!isAtEnd() && peek().tipo == TokenType.SEMICOLON) {
                advance();
            } else {
                throw new ParseError("Error: Punto y coma esperado después de la instrucción");
            }
            return expr;
        }
    }
    private ASTNode printStatement() {
        expect(TokenType.OUTPUT, "Se esperaba 'cout'");
        expect(TokenType.OPERATOR, "<<");
        Token identifier = expect(TokenType.IDENTIFIER, "Se esperaba un identificador después de '<<'");
        if (!isVariableDeclared(identifier)) {
            throw new ParseError("Error: Variable '" + identifier.valor + "' no declarada");
        }
        expect(TokenType.SEMICOLON, "Se esperaba ';' después de la instrucción");
        return new ASTNode(TokenType.OUTPUT, identifier.valor);
    }
    
}

