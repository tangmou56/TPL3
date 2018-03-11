import java.util.*;

public class Database{
	private ArrayList<String> lst;

	public Database(){
		lst=new ArrayList<String>();
	}



	//recu un id,retourne si il est deja connecté.
	//si non,l'ajoute dans la liste
	public boolean idrec(String id){
		int i;
		for(i=0;i<lst.size();i++){
			if(lst.get(i).compareTo(id)==0)
				return true;
		}
		lst.add(id);
		return false;
	}

	public void deconnect(String id){
		int i;
		for(i=0;i<lst.size();i++){
			if(lst.get(i).compareTo(id)==0){
				lst.remove(i);
				return ;
			}
		}
	}



}
