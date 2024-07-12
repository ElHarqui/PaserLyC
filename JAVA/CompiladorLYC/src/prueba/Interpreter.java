package prueba;

import java.util.Map;

public class Interpreter {

    private Map<String, String> symbolTable;

    public Interpreter(Map<String, String> symbolTable) {
        this.symbolTable = symbolTable;
    }

    public void interpret(ASTNode node) {
        if (node == null) {
            return;
        }
        switch (node.type) {
            case OUTPUT:
                printVariable(node.value);
                break;
            case OPERATOR:
                // Interpretar operadores (por ejemplo, +, -, *, /)
                interpret(node.left);
                interpret(node.right);
                break;
            case IDENTIFIER:
            case INTEGER:
            case FLOAT:
                // Manejar identificadores y literales
                break;
            default:
                throw new RuntimeException("Tipo de nodo no soportado: " + node.type);
        }
    }

    private void printVariable(String variableName) {
        if (!symbolTable.containsKey(variableName)) {
            throw new RuntimeException("Variable '" + variableName + "' no declarada");
        }
        System.out.println(symbolTable.get(variableName));
    }
}
