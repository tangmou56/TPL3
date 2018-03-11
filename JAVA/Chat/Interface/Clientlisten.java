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
	private Panneau pan;
	public Clientlisten(BufferedInputStream reader,Panneau pan){
  		this.reader=reader;
			this.pan=pan;
	}



	public void process(){
      String msg;
      int stream;
      byte[] b = new byte[4096];
	    try {
          while(!over){
            stream=reader.read(b);
            msg = new String(b, 0, stream);
						if(msg.startsWith("/l")){
							System.out.println("recive list");
							msg.replace("/l","");
							
							pan.con().setText(msg);
						}
						else{
            	System.out.println(msg);
							pan.dis().append(msg+"\n");
						}
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
