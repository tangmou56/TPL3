import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;
import java.util.Date;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



//ecoute les messages de serveur
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
            		//recu la liste les utilisateur connecté
					if(msg.startsWith("/l")){
						pan.con().setText("");
						System.out.println("recive list");
						msg=msg.replace("/l","");
						String[] ls=msg.split(",");
						for(int i=0;i<ls.length;i++)
							pan.con().append(ls[i]+"\n");				
					}
					else{
            			System.out.println(msg);
						pan.dis().append(msg+"\n");
						JScrollBar scrollBar=pan.sdis().getVerticalScrollBar();
						scrollBar.setValue(scrollBar.getMaximum());
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
