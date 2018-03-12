
import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.*;
public class Client{
  private String nom;
  private String host;
  private int port;
  private Panneau pan;
  private PrintWriter writer = null;
  private BufferedInputStream reader = null;
  private Clientlisten cl;
  public Client(String nom,String host,int port,Panneau pan){
    this.nom=nom;
    this.host=host;
    this.port=port;
    this.pan=pan;
  }

   public boolean open() {
      int stream;
      Scanner sc = new Scanner(System.in);
      String command;
      Socket connexion=null;
      byte[] b = new byte[4096];

      boolean over=false;
      try {
          connexion = new Socket(host, port);
      } catch (UnknownHostException e) {
          e.printStackTrace();
          return false;
      } catch (IOException e) {
          e.printStackTrace();
          return false;
      }
      try {
          writer = new PrintWriter(connexion.getOutputStream(), true);
          reader = new BufferedInputStream(connexion.getInputStream());

          writer.write(nom);
          writer.flush();
          stream=reader.read(b);
          command = new String(b, 0, stream);
          if(command.compareTo("ko")==0){
              System.out.println("nom existe");
              return false;
          }
          else{
              cl=new Clientlisten(reader,pan);
              Thread t = new Thread(cl);
              t.start();
              return true;

          }
      }catch (IOException e1) {
            e1.printStackTrace();
            return false;
      }
   }


   public void sendmsg(String msg){
       writer.write(msg);
       writer.flush();
       System.out.println("msg envoye");
       

   }

   public void close(){
      cl.shutdown();
      sendmsg("/q");

   }


}
