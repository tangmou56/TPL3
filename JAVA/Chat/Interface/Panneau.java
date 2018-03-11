import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Panneau extends JPanel {

  private JLabel lbnom = new JLabel("Nom");
  private JLabel lbip= new JLabel("IP");
  private JLabel lbport = new JLabel("Port");
  private JLabel lbcon = new JLabel("Connectés");
  private JLabel lbdis = new JLabel("Discussion");
  private JLabel lbmes = new JLabel("Message");
  private JTextField nom=new JTextField(15);
  private JButton con=new JButton("connection");
  private JTextField ip=new JTextField(15);
  private JTextField port=new JTextField(15);
  private JButton envo=new JButton("envoyer");
  private JTextArea textcon = new JTextArea(5, 15);
  private JTextArea textdis = new JTextArea(5, 15);
  private JTextField textmes=new JTextField(15);
  private Client client;
  public Panneau(){





      Box vbox=Box.createVerticalBox();
      Box vbox2=Box.createVerticalBox();
      Box vbox3=Box.createVerticalBox();
      Box hbox1=Box.createHorizontalBox();
      Box hbox2=Box.createHorizontalBox();
      Box hbox3=Box.createHorizontalBox();



      Panneau pan=this;
      con.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String n=nom.getText();
                String h=ip.getText();
                int p=Integer.parseInt(port.getText());
                client=new Client(n,h,p,pan);
                client.open();
            }
        });


        envo.addActionListener(new ActionListener() {

              @Override
              public void actionPerformed(ActionEvent e) {
                  client.sendmsg(textmes.getText());
              }
          });




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

  public JTextArea dis(){
    return textdis;
  }

  public JTextArea con(){
    return textcon;
  }


}
