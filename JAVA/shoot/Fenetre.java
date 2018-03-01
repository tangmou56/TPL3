
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
 
public class Fenetre extends JFrame {

  public static void main(String[] args) {
    new Fenetre();
  }

  private Panneau pan = new Panneau();

  public Fenetre() {
    this.setTitle("Animation");
    this.setSize(300, 300);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setLocationRelativeTo(null);
    this.setContentPane(pan);
    this.setVisible(true);

    go();
  }

  private void go() {
    int x = pan.getPosX(), y = pan.getPosY();
    boolean backX = false;
    boolean backY = false;
	pan.setPosX(10);
	pan.setPosY(10);

	
    while (true) { 
		pan.repaint();
      try {
        Thread.sleep(3);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}