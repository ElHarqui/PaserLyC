package prueba;

import java.util.HashMap;
import java.util.Map;

public class Interpreter {
    private ASTNode root;
    private Map<String, Object> variableValues;

    public Interpreter(ASTNode root) {
        this.root = root;
        this.variableValues = new HashMap<>();
    }

    public void interpret() {
        evaluate(root);
    }

    private Object evaluate(ASTNode node) {
        if (node == null) {
            return null;
        }
        System.out.println("Evaluando nodo: " + node.type + " con valor: " + node.value);

        switch (node.type) {
            case INTEGER:
                return Integer.parseInt(node.value);
            case FLOAT:
                return Double.parseDouble(node.value);
            case STRING:
                return node.value;
            case IDENTIFIER:
                if (variableValues.containsKey(node.value)) {
                    return variableValues.get(node.value);
                } else {
                    throw new IllegalArgumentException("Variable no declarada: " + node.value);
                }
            case DATA_TYPE:
                if (node.left != null && node.left.type == TokenType.IDENTIFIER && node.right != null) {
                    variableValues.put(node.left.value, evaluate(node.right));
                    return null;
                } else {
                    throw new IllegalArgumentException("Declaración de variable incorrecta");
                }
            case OPERATOR:
                switch (node.value) {
                    case "+":
                        return (int) evaluate(node.left) + (int) evaluate(node.right);
                    case "-":
                        return (int) evaluate(node.left) - (int) evaluate(node.right);
                    case "*":
                        return (int) evaluate(node.left) * (int) evaluate(node.right);
                    case "/":
                        return (int) evaluate(node.left) / (int) evaluate(node.right);
                    default:
                        throw new IllegalArgumentException("Operador desconocido: " + node.value);
                }
            case OUTPUT:
                if ("cout <<".equals(node.value)) {
                    System.out.println(evaluate(node.left));
                    return null;
                }
                // Otros casos de OUTPUT
                return node.value;
            default:
                throw new IllegalArgumentException("Tipo de nodo desconocido: " + node.type);
        }
    }
}
