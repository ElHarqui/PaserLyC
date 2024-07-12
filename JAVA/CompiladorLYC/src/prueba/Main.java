package prueba;

import java.util.List;

public class Main {
    public static void main(String[] args) {
        String codigoFuente = "int x = 42; x = x + 1 +6; cout << x-1;";
        Lexer lexer = new Lexer(codigoFuente);
        List<Token> tokens = lexer.tokenize();
        Parser parser = new Parser(tokens);
        ASTNode root = parser.parse();
        Interpreter interpreter = new Interpreter(root);
        interpreter.interpret();
    }
}
