import java.util.*;
import java.io.IOException;
import java.net.*;
import java.io.BufferedInputStream;

import java.io.PrintWriter;

import java.text.DateFormat;

public class Database{
	private ArrayList<String> lst;
	private ArrayList<Socket> connected=new ArrayList<Socket>();
	public Database(){
		lst=new ArrayList<String>();
	}



	//recu un id,retourne si il est deja connecté.
	//si non,l'ajoute dans la liste
	public boolean newone(String id,Socket sock){
		int i;
		for(i=0;i<lst.size();i++){
			if(lst.get(i).compareTo(id)==0)
				return true;
		}
		lst.add(id);
		connected.add(sock);
		return false;
	}

	public void deconnect(String id){
		int i;
		for(i=0;i<lst.size();i++){
			if(lst.get(i).compareTo(id)==0){
				System.out.println(id+" deconnect");
				lst.remove(i);
				connected.remove(i);
				return ;
			}
		}
	}

	public ArrayList<String> listnom(){
		return lst;
	}

	public ArrayList<Socket> listconnected(){
		return connected;
	}



}
