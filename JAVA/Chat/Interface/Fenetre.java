
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class Fenetre extends JFrame {
  private Panneau pan;


  

  public Fenetre() {
    pan = new Panneau();
    this.setTitle("Chat");
    this.setSize(500, 500);
    this.setLayout(new FlowLayout());
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setLocationRelativeTo(null);
    this.setContentPane(pan);
    this.setVisible(true);

  }

  
    
  
}