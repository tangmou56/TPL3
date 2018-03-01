import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;
import java.util.Date;

public class ServerProcess implements Runnable {

	private Socket sock;
	private BufferedInputStream reader = null;
	private PrintWriter writer = null;

	public ServerProcess(Socket sock){
		this.sock=sock;
	}



	public void process(){
	    System.err.println("Lancement du traitement de la connexion cliente");

	    try {
	        
	        //Ici, nous n'utilisons pas les mêmes objets que précédemment
	        //Je vous expliquerai pourquoi ensuite
	        writer = new PrintWriter(sock.getOutputStream());
            reader = new BufferedInputStream(sock.getInputStream());
	            
	        //On attend la demande du client            
	        byte[] b = new byte[4096];
	        int stream = reader.read(b);
	        String response = new String(b, 0, stream);
            InetSocketAddress remote = (InetSocketAddress)sock.getRemoteSocketAddress();
	            
	        //On affiche quelques infos, pour le débuggage
	        String debug = "";
	        //debug = "Thread : " + Thread.currentThread().getName() + ". ";
	        debug += "Demande de l'adresse : " + remote.getAddress().getHostAddress() +".";
	        debug += " Sur le port : " + remote.getPort() + ".\n";
	        debug += "\t -> Commande reçue : " + response + "\n";
	        System.err.println("\n" + debug);      
	    }catch(SocketException e){
	        System.err.println("LA CONNEXION A ETE INTERROMPUE ! ");
	    } catch (IOException e) {
	        e.printStackTrace();
	    }         


	}

	public void run(){
		process();
	}

}
