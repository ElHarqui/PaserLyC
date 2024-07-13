package prueba;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Interpreter {
    private ASTNode root;
    private Map<String, Object> variableValues;
    private List<String> Resultados;

    public Interpreter(ASTNode root) {
        this.root = root;
        this.variableValues = new HashMap<>();
        this.Resultados = new ArrayList<>();
    }

    public List<String> getResultados() {
        return this.Resultados;
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
                if (node.left.type == TokenType.IDENTIFIER && node.right != null) {
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
                    case "=":
                        if (node.left.type == TokenType.IDENTIFIER) {
                            variableValues.put(node.left.value, evaluate(node.right));
                            return null;
                        } else {
                            throw new IllegalArgumentException("Asignación incorrecta");
                        }
                    case "<":
                        return (int) evaluate(node.left) < (int) evaluate(node.right);
                    case ">":
                        return (int) evaluate(node.left) > (int) evaluate(node.right);
                    case "<=":
                        return (int) evaluate(node.left) <= (int) evaluate(node.right);
                    case ">=":
                        return (int) evaluate(node.left) >= (int) evaluate(node.right);
                    case "!=":
                        return !evaluate(node.left).equals(evaluate(node.right));
                    default:
                        throw new IllegalArgumentException("Operador desconocido: " + node.value);
                }
            case OUTPUT:
                if ("cout <<".equals(node.value)) {
                    this.Resultados.add(String.valueOf(evaluate(node.left)));
                    return null;
                }
                return node.value;
            case SEMICOLON:
                evaluate(node.left);
                evaluate(node.right);
                return null;
            case LOOP:
                if ("while".equals(node.value)) {
                    while ((boolean) evaluate(node.left)) {
                        evaluate(node.right);
                    }
                    return null;
                }
                break;
            default:
                throw new IllegalArgumentException("Tipo de nodo desconocido: " + node.type);
        }
        return null;
    }
}
