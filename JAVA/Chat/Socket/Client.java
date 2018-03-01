
import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Random;
public class Client {

   public static void main(String[] args) {
    
      String host = "127.0.0.1";
      int port = 2345;
      Socket connexion=null;
      PrintWriter writer = null;
      BufferedInputStream reader = null;
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


      writer.write("commande");
      writer.flush();  
      }catch (IOException e1) {
            e1.printStackTrace();
      }
  

      
   }
}