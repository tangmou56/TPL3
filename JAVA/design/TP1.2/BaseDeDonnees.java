/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 15:24:03 CET 2018
*
*/

import java.util.List;
import java.util.LinkedList;
public class BaseDeDonnees<T extends Comparable<T>> {
	StrategieTri st;
	List<T> donnees;

	public BaseDeDonnees(StrategieTri s){
		st=s;
		donnees=new LinkedList<T>();
	}

	public void afficheDonneesTriees(){
		for(T element : st.trie(donnees)){
			System.out.println(element);
		}
	}

	
	public void ajouter(T el){
		donnees.add(el);
	}
	
}