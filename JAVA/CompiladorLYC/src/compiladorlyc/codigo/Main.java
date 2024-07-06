
package compiladorlyc.codigo;


import java.io.*;
import java.nio.file.*;
import java.util.List;



public class Main {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                System.out.println("Choose an option:");
                System.out.println("1. Run Lexer");
                System.out.println("2. Run Parser");
                System.out.println("3. Exit");

                int choice = Integer.parseInt(reader.readLine());

                if (choice == 3) break;

                System.out.print("Enter the source file name: ");
                String filename = reader.readLine();

                String source;
                try {
                    source = readFile(filename);
                } catch (IOException e) {
                    System.out.println(e.getMessage());
                    continue;
                }

                if (choice == 1) {
                    runLexer(source);
                } else if (choice == 2) {
                    runParser(source);
                }
            } catch (IOException e) {
                System.out.println("Error reading input: " + e.getMessage());
            }
        }
    }

    private static String readFile(String filename) throws IOException {
        return new String(Files.readAllBytes(Paths.get(filename)));
    }

    private static void runLexer(String source) {
        Lexer lexer = new Lexer(source);
        List<Token> tokens = lexer.tokenize();
        for (Token token : tokens) {
            System.out.println("Token Type: " + token.type + ", Value: " + token.value);
        }
    }

    private static void runParser(String source) {
        Lexer lexer = new Lexer(source);
        List<Token> tokens = lexer.tokenize();
        Parser parser = new Parser(tokens);
        try {
            ASTNode ast = parser.parse();
            System.out.println("Parsing successful!");
        } catch (RuntimeException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}

