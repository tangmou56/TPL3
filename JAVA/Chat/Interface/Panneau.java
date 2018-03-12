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
  private JTextField nom=new JTextField(5);
  private JButton con=new JButton("connection");
  private JTextField ip=new JTextField(5);
  private JTextField port=new JTextField(5);
  private JButton envo=new JButton("envoyer");
  private JTextArea textcon = new JTextArea(20, 5);
  private JTextArea textdis = new JTextArea(20, 30);
  private JTextField textmes=new JTextField(15);
  private JScrollPane scrolldis = new JScrollPane(); 
  private JScrollPane scrollcon = new JScrollPane(); 
  private Client client;
  private boolean connected=false;
  public Panneau(){

      ip.setText("127.0.0.1");
      port.setText("2345");

      envo.setEnabled(false);
      textcon.setEditable(false);
      textdis.setEditable(false);

      scrolldis.setHorizontalScrollBarPolicy( 
      JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS); 
      scrolldis.setVerticalScrollBarPolicy( 
      JScrollPane.VERTICAL_SCROLLBAR_ALWAYS); 

      scrolldis.setBounds(28, 209, 752, 265);
      textdis.setBounds(28, 209, 752, 265);
      scrolldis.setViewportView(textdis);


      scrollcon.setHorizontalScrollBarPolicy( 
      JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS); 
      scrollcon.setVerticalScrollBarPolicy( 
      JScrollPane.VERTICAL_SCROLLBAR_ALWAYS); 
      scrollcon.setViewportView(textcon);


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
                
                if(!connected){
                    String n=nom.getText();
                    if(n.contains("/l")){
                        textdis.append("nom invalide\n");
                        return;
                    }

                    String h=ip.getText();
                    int p=Integer.parseInt(port.getText());
                    client=new Client(n,h,p,pan);
                    if(client.open()){
                        connected=true;
                        nom.setEditable(false);
                        ip.setEditable(false);
                        port.setEditable(false);
                        con.setText("déconnection");
                        envo.setEnabled(true);
                        addtext("Connecté\n");
                    }
                    else{
                        addtext("connexion impossible\n");
                    }
                    
                }
                else{
                    connected=false;
                    nom.setEditable(true);
                    ip.setEditable(true);
                    port.setEditable(true);
                    con.setText("connection");
                    client.close();
                    envo.setEnabled(false);
                    addtext("deconnecte\n");
                }
            }
        });


        envo.addActionListener(new ActionListener() {

              @Override
              public void actionPerformed(ActionEvent e) {
                  if(textmes.getText().compareTo("/q")==0)
                    client.sendmsg(" /q");
                  else if(textmes.getText().startsWith("/l"))
                    client.sendmsg(textmes.getText().replace("/l"," /l"));
                  else
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
      vbox3.add(scrollcon);
      vbox2.add(lbdis);
      vbox2.add(scrolldis);
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

  public JScrollPane sdis(){
    return scrolldis;
  }

  public void addtext(String msg){
    textdis.append(msg);
    JScrollBar scrollBar=scrolldis.getVerticalScrollBar();
    scrollBar.setValue(scrollBar.getMaximum());
  }


  public void deconnecte(){
      connected=false;
      nom.setEditable(true);
      ip.setEditable(true);
      port.setEditable(true);
      con.setText("connection");
      client.close();
      envo.setEnabled(false);
      addtext("deconnecte\n");
  }


}
