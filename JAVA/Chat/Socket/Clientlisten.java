import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;
import java.util.Date;

public class Clientlisten implements Runnable {

	private Socket sock;
	private BufferedInputStream reader = null;
  private boolean over=false;
	public Clientlisten(BufferedInputStream reader){
  		this.reader=reader;
	}



	public void process(){
      String msg;
      int stream;
      byte[] b = new byte[4096];
	    try {
          while(!over){
            stream=reader.read(b);
            msg = new String(b, 0, stream);
            System.out.println(msg);
          }
			}
	    catch(SocketException e){
            System.err.println("LA CONNEXION A ETE INTERROMPUE ! ");
	    } catch (IOException e) {
	          e.printStackTrace();
	    }


	}

	public void run(){
			process();
	}

  public void shutdown(){
    over=true;
  }


}
