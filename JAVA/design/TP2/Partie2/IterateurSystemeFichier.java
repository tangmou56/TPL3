/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 09:27:50 CET 2018
*
*/
import java.util.*;
public class IterateurSystemeFichier implements Iterator<Unite>{
	private int index;
	private List<Unite> list;


	public IterateurSystemeFichier(List<Unite> list){
		this.list=list;
		index=list.size()-1;
	}
	
	public boolean hasNext(){
		return index!=-1;
	}

	public Unite next(){
		return list.get(index--);
	}

	public void remove(){
		list.remove(index);
		index--;
	}
	
}