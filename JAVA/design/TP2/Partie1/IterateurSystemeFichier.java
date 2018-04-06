/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 09:27:50 CET 2018
*
*/
import java.util.*;
public class IterateurSystemeFichier implements Iterator<Fichier>{
	private int index=0;
	private List<Fichier> list;


	public IterateurSystemeFichier(List<Fichier> list){
		this.list=list;
	}
	
	public boolean hasNext(){
		return index!=list.size();
	}

	public Fichier next(){
		return list.get(index++);
	}

	
}