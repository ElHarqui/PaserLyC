package prueba;

public class ASTNode {
    TokenType type;
    String value;
    ASTNode left;
    ASTNode right;

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
}
