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
	private Database db;
	public ServerProcess(Socket sock,Database db){
		this.sock=sock;
		this.db=db;
	}



	public void process(){
	    System.err.println("Lancement du traitement de la connexion cliente");

	    try {
					int port;
					boolean over=false;
					String nom;
	        //Ici, nous n'utilisons pas les mêmes objets que précédemment
	        //Je vous expliquerai pourquoi ensuite
	        writer = new PrintWriter(sock.getOutputStream());
          reader = new BufferedInputStream(sock.getInputStream());

	        //On attend la demande du client
	        byte[] b = new byte[4096];
	        int stream;
	        String response;
          InetSocketAddress remote = (InetSocketAddress)sock.getRemoteSocketAddress();

	        //On affiche quelques infos, pour le débuggage
	        String debug = "";
	        //debug = "Thread : " + Thread.currentThread().getName() + ". ";
	        debug += "Demande de l'adresse : " + remote.getAddress().getHostAddress() +".";
					port=remote.getPort();
	        System.err.println("\n" + debug);

					stream=reader.read(b);
					nom = new String(b, 0, stream);
					if(db.idrec(nom)){
						System.out.println("nom existe");
						writer.write("ko");
			      writer.flush();
					}
					else{
						writer.write("ok");
						writer.flush();
						while(!over){
							stream=reader.read(b);
							response = new String(b, 0, stream);
							System.out.println(nom+":"+response);
							if(response.compareTo("/q")==0)
								over=true;
						}

						System.out.println(nom+"deconnect");
						db.deconnect(nom);
				}


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
