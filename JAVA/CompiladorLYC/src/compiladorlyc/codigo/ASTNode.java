
package compiladorlyc.codigo;

public class ASTNode {
    TokenType type;
    String value;
    ASTNode left;
    ASTNode right;

    ASTNode(TokenType type, String value) {
        this.type = type;
        this.value = value;
        this.left = null;
        this.right = null;
    }
}
