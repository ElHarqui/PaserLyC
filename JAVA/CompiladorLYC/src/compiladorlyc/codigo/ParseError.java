
package compiladorlyc.codigo;


public class ParseError extends RuntimeException {
    public ParseError(String message) {
        super(message);
    }
}