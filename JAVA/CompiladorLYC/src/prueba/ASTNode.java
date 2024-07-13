package prueba;

import java.util.List;

public class ASTNode {
    TokenType type;
    String value;
    ASTNode left;
    ASTNode right;
    List<ASTNode> children;

    public ASTNode(TokenType type, String value) {
        this.type = type;
        this.value = value;
        this.left = null;
        this.right = null;
    }

    public ASTNode(TokenType type, String value, ASTNode left, ASTNode right) {
        this.type = type;
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public ASTNode(TokenType type, String value, ASTNode left) {
        this.type = type;
        this.value = value;
        this.left = left;
        this.right = null;
    }
    public ASTNode(TokenType type, String value, List<ASTNode> children) {
        this.type = type;
        this.value = value;
        this.children = children;
    }
}
