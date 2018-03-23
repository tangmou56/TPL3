import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.* ;
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
  private JTextPane textpan = new JTextPane();
  private JTextField textmes=new JTextField(15);
  private JScrollPane scrolldis = new JScrollPane();
  private JScrollPane scrollcon = new JScrollPane();
  private Client client;
  private boolean connected=false;
  private JComboBox comboBox=new JComboBox();


  public Panneau(){

      ip.setText("127.0.0.1");
      port.setText("2345");


      envo.setEnabled(false);
      textcon.setEditable(false);
      textpan.setEditable(false);
      textpan.setPreferredSize(new Dimension(350,300));
      scrolldis.setHorizontalScrollBarPolicy(
      JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
      scrolldis.setVerticalScrollBarPolicy(
      JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);



      scrolldis.setViewportView(textpan);
      scrolldis.setPreferredSize(new Dimension(350,300));

      scrollcon.setHorizontalScrollBarPolicy(
      JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
      scrollcon.setVerticalScrollBarPolicy(
      JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
      scrollcon.setViewportView(textcon);

      comboBox.addItem("Red");
      comboBox.addItem("Blue");
      comboBox.addItem("Yellow");

      Box vbox=Box.createVerticalBox();
      Box vbox2=Box.createVerticalBox();
      Box vbox3=Box.createVerticalBox();
      Box hbox1=Box.createHorizontalBox();
      Box hbox2=Box.createHorizontalBox();
      Box hbox3=Box.createHorizontalBox();
      Box hbox4=Box.createHorizontalBox();


      Panneau pan=this;

      con.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {

                if(!connected){
                    String n=nom.getText();
                    if(n.contains("/l")){
                        addtext("nom invalide\n");
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
                        con.setText("deconnnection");
                        envo.setEnabled(true);
                        addtext("Connecté");

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
                    addtext("deconnecte");
                    client=null;

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
                    client.sendmsg("/"+comboBox.getSelectedIndex()+textmes.getText());
              }
          });



          ip.getDocument().addDocumentListener(new DocumentListener() {
                @Override
                public void changedUpdate(DocumentEvent e){
                        checkok();
                }
                public void removeUpdate(DocumentEvent e) {
                        checkok();
                }
                public void insertUpdate(DocumentEvent e) {
                        checkok();
                }
            });
            nom.getDocument().addDocumentListener(new DocumentListener() {
                  @Override
                  public void changedUpdate(DocumentEvent e){
                          checkok();
                  }
                  public void removeUpdate(DocumentEvent e) {
                          checkok();
                  }
                  public void insertUpdate(DocumentEvent e) {
                          checkok();
                  }
              });
              port.getDocument().addDocumentListener(new DocumentListener() {
                    @Override
                    public void changedUpdate(DocumentEvent e){
                            checkok();
                    }
                    public void removeUpdate(DocumentEvent e) {
                            checkok();
                    }
                    public void insertUpdate(DocumentEvent e) {
                            checkok();
                    }
              });

      con.setEnabled(false);

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
      hbox4.add(envo);
      hbox4.add(comboBox);
      vbox2.add(hbox4);
      hbox3.add(vbox2);
      vbox.add(hbox1);
      vbox.add(hbox2);
      vbox.add(hbox3);
      this.add(vbox);


  }


  public void paintComponent(Graphics g) {

  }

  public JTextPane dis(){
    return textpan;
  }

  public JTextArea con(){
    return textcon;
  }

  public JScrollPane sdis(){
    return scrolldis;
  }

  //ajoute du text dans la region de discussion
  public void addtext(String msg){
    Color color=Color.black;
    if(msg.contains("/0")){
        msg=msg.replace("/0","");
        color=Color.red;
    }
    if(msg.contains("/1")){
        msg=msg.replace("/1","");
        color=Color.blue;
    }
    if(msg.contains("/2")){
        msg=msg.replace("/2","");
        color=Color.yellow;
    }

    StyledDocument doc = textpan.getStyledDocument();
    Style style = textpan.addStyle("I'm a Style", null);
    StyleConstants.setForeground(style, color);
    try
    {
        doc.insertString(doc.getLength(), msg+"\n", style );
    }
    catch(Exception e) { System.out.println(e); }

    //textdis.append(msg);
    JScrollBar scrollBar=scrolldis.getVerticalScrollBar();
    scrollBar.setValue(scrollBar.getMaximum());
  }


  public void checkok(){
    if(!ip.getText().equals("")&&!port.getText().equals("")&&!nom.getText().equals(""))
        con.setEnabled(true);
    else
        con.setEnabled(false);
  }

  public Client client(){
    return client;
  }


}
