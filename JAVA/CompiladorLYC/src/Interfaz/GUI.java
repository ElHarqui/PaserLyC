
package Interfaz;

import java.util.List;
import prueba.ASTNode;
import prueba.Interpreter;
import prueba.Lexer;
import prueba.ParseError;
import prueba.Parser;
import prueba.Token;
import prueba.TokenType;

public class GUI extends javax.swing.JFrame {

    /**
     * Creates new form NewJFrame
     */
    public GUI() {
        initComponents();

    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        Limpiar = new javax.swing.JButton();
        Salir = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        Ejecutar = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        textAreaEntrada = new javax.swing.JTextArea();
        jScrollPane2 = new javax.swing.JScrollPane();
        textAreaSalida = new javax.swing.JTextArea();
        jScrollPane4 = new javax.swing.JScrollPane();
        CoutSalida = new javax.swing.JTextArea();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setLayout(null);

        Limpiar.setText("Limpiar");
        Limpiar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                LimpiarActionPerformed(evt);
            }
        });
        jPanel1.add(Limpiar);
        Limpiar.setBounds(300, 430, 70, 20);

        Salir.setText("Salir");
        Salir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SalirActionPerformed(evt);
            }
        });
        jPanel1.add(Salir);
        Salir.setBounds(430, 430, 75, 20);

        jLabel1.setFont(new java.awt.Font("Microsoft JhengHei", 1, 24)); // NOI18N
        jLabel1.setText("expresiones aritmeticas");
        jPanel1.add(jLabel1);
        jLabel1.setBounds(190, 20, 340, 40);

        Ejecutar.setText("Ejecutar");
        Ejecutar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                EjecutarActionPerformed(evt);
            }
        });
        jPanel1.add(Ejecutar);
        Ejecutar.setBounds(140, 430, 75, 20);

        textAreaEntrada.setColumns(20);
        textAreaEntrada.setLineWrap(true);
        textAreaEntrada.setRows(5);
        textAreaEntrada.setWrapStyleWord(true);
        jScrollPane1.setViewportView(textAreaEntrada);

        jPanel1.add(jScrollPane1);
        jScrollPane1.setBounds(40, 90, 270, 170);

        textAreaSalida.setEditable(false);
        textAreaSalida.setColumns(20);
        textAreaSalida.setLineWrap(true);
        textAreaSalida.setRows(5);
        textAreaSalida.setWrapStyleWord(true);
        jScrollPane2.setViewportView(textAreaSalida);

        jPanel1.add(jScrollPane2);
        jScrollPane2.setBounds(333, 92, 280, 310);

        CoutSalida.setEditable(false);
        CoutSalida.setColumns(20);
        CoutSalida.setRows(5);
        CoutSalida.setWrapStyleWord(true);
        jScrollPane4.setViewportView(CoutSalida);

        jPanel1.add(jScrollPane4);
        jScrollPane4.setBounds(40, 310, 280, 86);

        jLabel2.setText("Codigo:");
        jPanel1.add(jLabel2);
        jLabel2.setBounds(50, 70, 50, 16);

        jLabel3.setText("jLabel3");
        jPanel1.add(jLabel3);
        jLabel3.setBounds(350, 70, 37, 16);

        jLabel4.setText("Consola :");
        jPanel1.add(jLabel4);
        jLabel4.setBounds(50, 290, 60, 16);

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 660, 500));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void EjecutarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_EjecutarActionPerformed
        String sourceCode = textAreaEntrada.getText().trim();

        Lexer lexer = new Lexer(sourceCode);
        List<Token> tokens = lexer.tokenize();
        boolean tokenizacionCorrecta = true;

       

        if (tokenizacionCorrecta) {
            textAreaSalida.append("\nTokenización correcta!\n");

            Parser parser = new Parser(tokens);
         
            StringBuilder tokenOutput = new StringBuilder();

            for (Token token : tokens) {
                if (token.equals(parser.getcurrent())) {
                    tokenOutput.append("\nERROR en la posición: ").append(tokenOutput.length()).append("\n").append(token).append("\n");
                    break;
                }
                tokenOutput.append(token).append("\n");
            }

            textAreaSalida.append(tokenOutput.toString());

            String tokenMessage = "TOKENS CORRECTO\n";
            System.out.println(tokenMessage); // Imprime en consola
            ASTNode root = parser.parse();
            Interpreter interpreter = new Interpreter(root);
            interpreter.interpret();
           
            StringBuilder coutOutput = new StringBuilder();
            List<String> Resultados = interpreter.getResultados();
            for (String resul : Resultados) {
                coutOutput.append(resul).append("\n");
            }
            
            CoutSalida.append(coutOutput.toString());
        } 

    }//GEN-LAST:event_EjecutarActionPerformed

    private void SalirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SalirActionPerformed
        System.exit(0);
    }//GEN-LAST:event_SalirActionPerformed

    private void LimpiarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_LimpiarActionPerformed
        textAreaEntrada.setText("");
        textAreaSalida.setText("");
        CoutSalida.setText("");
        

    }//GEN-LAST:event_LimpiarActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(() -> {
            new GUI().setVisible(true);
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextArea CoutSalida;
    private javax.swing.JButton Ejecutar;
    private javax.swing.JButton Limpiar;
    private javax.swing.JButton Salir;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane4;
    private javax.swing.JTextArea textAreaEntrada;
    private javax.swing.JTextArea textAreaSalida;
    // End of variables declaration//GEN-END:variables
}
