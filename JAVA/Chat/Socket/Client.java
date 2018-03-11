
import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.*;
public class Client {

   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      String host = "127.0.0.1";
      String nom;
      int stream;
      System.out.println("Saisir nom");
      nom=sc.nextLine();
      String command;
      int port = 2345;
      Socket connexion=null;
      byte[] b = new byte[4096];
      PrintWriter writer = null;
      BufferedInputStream reader = null;
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
        while(!over){
          command=sc.nextLine();
          writer.write(command);
          writer.flush();
          System.out.println("msg envoye");
          if(command.compareTo("/q")==0)
            over=true;
        }
        System.out.println("deconnect");

      }
      }catch (IOException e1) {
            e1.printStackTrace();
      }



   }
}
