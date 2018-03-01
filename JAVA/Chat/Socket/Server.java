

import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;
import java.util.Date;

public class Server {

   public static void main(String[] args){
    
      String host = "127.0.0.1";
      int port = 2345;
      ServerSocket server = null;
      
      Socket sock=null;
      
      System.out.println("Serveur initialisé.");
      try {
         server = new ServerSocket(port, 100, InetAddress.getByName(host));
      } catch (UnknownHostException e) {
         e.printStackTrace();
      } catch (IOException e) {
         e.printStackTrace();
      }

      //listening
      while(true){
         try {
            sock = server.accept();
            System.out.println("Connexion cliente reçue.");
            Thread t = new Thread(new ServerProcess(sock));
            t.run();
         }catch (IOException e) {
            e.printStackTrace();
         }
      }



   }



   



}