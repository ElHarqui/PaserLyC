
package prueba;

public class Token {

    public TokenType tipo;
    public String valor;

    public Token(TokenType tipo, String valor) {
        this.tipo = tipo;
        this.valor = valor;
    }

    @Override
    public String toString() {
        switch (tipo) {
            case IDENTIFIER:
                return "ID: " + valor;
            case OPERATOR:
                return "Operador: " + valor;
            case SEMICOLON:
                return "Punto y coma: " + valor;
            case DELIMITER:
                return "Delimitador: " + valor;
            case STRING:
                return "Cadena: \"" + valor + "\"";
            case PREPROCESSOR:
                return "Directiva de preprocesador: " + valor;
            case END_OF_FILE:
                return "Fin de archivo";
            case KEYWORD:
                return " Tipo de dato: " + valor;
            case INTEGER:
                return "Entero: " + valor;
            case FLOAT:
                return "Flotante: " + valor;
            case DATA_TYPE:
                return "Numero : " + valor;
            case DOUBLE_QUOTE:
                return "Comillas dobles (\")";
            case SINGLE_QUOTE:
                return " (')";
            case CASE_SYMBOL:
                return "(' ')";
            case INCREMENT:
                return " Incremento ++";
            case SHIFT_LEFT:
                return "(<<)";
            case SHIFT_RIGHT:
                return "(>>)";
            case CONDITIONAL:
                return "Sentencia condicional: " + valor;
            case FOR:
                return "Bucle for: " + valor;
            case LOOP:
                return "Bucle while: " + valor;
            case OUTPUT:
                return "Salida: " + valor;
            case INPUT:
                return "Entrada: " + valor;
            default:
                return "Tipo no reconocido";
        }
    }

}
