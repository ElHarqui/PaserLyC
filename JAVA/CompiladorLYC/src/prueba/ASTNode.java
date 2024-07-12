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

}

