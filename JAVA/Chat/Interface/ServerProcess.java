import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;
import java.util.*;

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
	        debug += "sur port:"+port;
					stream=reader.read(b);
					nom = new String(b, 0, stream);
					debug += "nom:"+nom;
					System.err.println("\n" + debug);

					if(db.newone(nom,sock)){
						System.out.println("nom existe");
						writer.write("ko");
			      writer.flush();
					}
					else{
						writer.write("ok");
						writer.flush();

						String list=String.join(",", db.listnom());
						broadcast("/l"+list);


						while(!over){
							stream=reader.read(b);
							response = new String(b, 0, stream);
							System.out.println(nom+":"+response);

							if(response.compareTo("/q")==0)
								over=true;
							/*else if(response.compareTo("/l")==0){
								String list=String.join(",", db.listnom());
								writer.write(list);
								writer.flush();
							}*/
							else{
								broadcast(nom+":"+response);
							}

						}
						db.deconnect(nom);
						list=String.join(",", db.listnom());
						broadcast("/l"+list);
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


	public void broadcast(String msg){
			PrintWriter writer = null;
			ArrayList<Socket> l=db.listconnected();
			Socket sock;
			for(int i=0;i<l.size();i++){
					sock=l.get(i);
					if(sock!=this.sock){
							try{
								writer=new PrintWriter(sock.getOutputStream());
							}catch (IOException e1) {
				        e1.printStackTrace();
				      }

							writer.write(msg);
							writer.flush();
					}
					else{
							this.writer.write(msg);
							this.writer.flush();
					}
			}
	}

}
