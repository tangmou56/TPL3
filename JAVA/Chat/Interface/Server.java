

import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;
import java.util.*;
public class Server {

  private ServerSocket server = null;
  private Database db=new Database();
  

   public void open(){

      String host = "127.0.0.1";
      int port = 2345;


      try {
         server = new ServerSocket(port, 100, InetAddress.getByName(host));
      } catch (UnknownHostException e) {
         e.printStackTrace();
      } catch (IOException e) {
         e.printStackTrace();
      }





      Thread t = new Thread(new Runnable(){
         public void run(){
            while(true){

              try {
                 Socket sock = server.accept();
                 System.out.println("Connexion cliente reçue.");
                 Thread t = new Thread(new ServerProcess(sock,db));
                 t.start();
              }catch (IOException e) {
                 e.printStackTrace();
              }
            }

         }
      });
        t.start();



   }






}
