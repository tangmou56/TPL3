import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Panneau extends JPanel {



  public Panneau(){

      

      JLabel lbnom = new JLabel("Nom"); 
      JLabel lbip= new JLabel("IP");
      JLabel lbport = new JLabel("Port");
      JLabel lbcon = new JLabel("Connectés");
      JLabel lbdis = new JLabel("Discussion");
      JLabel lbmes = new JLabel("Message");  
      JTextField nom=new JTextField(15);
      JButton con=new JButton("connection");
      JTextField ip=new JTextField(15);
      JTextField port=new JTextField(15);
      JButton envo=new JButton("envoyer");
      JTextArea textcon = new JTextArea(5, 15);
      JTextArea textdis = new JTextArea(5, 15);
      JTextField textmes=new JTextField(15);

      Box vbox=Box.createVerticalBox();
      Box vbox2=Box.createVerticalBox();
      Box vbox3=Box.createVerticalBox();
      Box hbox1=Box.createHorizontalBox();
      Box hbox2=Box.createHorizontalBox();
      Box hbox3=Box.createHorizontalBox();



      hbox1.add(lbnom);
      hbox1.add(nom);
      hbox1.add(con);
      hbox2.add(lbip);
      hbox2.add(ip);
      hbox2.add(lbport);
      hbox2.add(port);
      hbox3.add(vbox3);
      vbox3.add(lbcon);
      vbox3.add(textcon);
      vbox2.add(lbdis);
      vbox2.add(textdis);
      vbox2.add(lbmes);
      vbox2.add(textmes);
      vbox2.add(envo);
      hbox3.add(vbox2);
      vbox.add(hbox1);
      vbox.add(hbox2);
      vbox.add(hbox3);
      this.add(vbox);


  }


  public void paintComponent(Graphics g) {

  }

  
}