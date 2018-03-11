
import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.*;
public class Client implements Runnable{
  private String nom;
  private String host;
  private int port;
  private Panneau pan;
  private PrintWriter writer = null;
  private BufferedInputStream reader = null;
  public Client(String nom,String host,int port,Panneau pan){
    this.nom=nom;
    this.host=host;
    this.port=port;
    this.pan=pan;
  }

   public void open() {
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
      } catch (IOException e) {
          e.printStackTrace();
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
          }
          else{
              Thread t = new Thread(new Clientlisten(reader,pan));
              t.start();

          }
      }catch (IOException e1) {
            e1.printStackTrace();
      }
   }


   public void sendmsg(String msg){
       //int stream;
       //byte[] b = new byte[4096];
       writer.write(msg);
       writer.flush();
       System.out.println("msg envoye");
       /*
       if(msg.compareTo("/q")==0)
           over=true;
       if(msg.compareTo("/l")==0){
           stream=reader.read(b);
           msg = new String(b, 0, stream);
           System.out.println(msg);
       }*/
   }


   public void run(){
 			open();
 	  }
}
