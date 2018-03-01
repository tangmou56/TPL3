/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 15:17:17 CET 2018
*
*/
import java.util.List;
import java.util.Collections;
import java.util.LinkedList;

public class TriInsertion implements StrategieTri{

	private static TriInsertion tri=null;

	public static TriInsertion getInstance(){
		if(tri==null){
			tri=new TriInsertion();
		}
		return tri;
	}

	public <T extends Comparable<T>>  List<T> trie(List<T> donnees){
		List<T> resultat = new LinkedList<T>();
		int i;
		boolean insertion;

		for(T element: donnees){
			for (i=0,insertion=false;i< resultat.size();i++){
				if(element.compareTo(resultat.get(i) )>0){
					resultat.add(i,element);
					insertion=true;
					break;
				}
			}
			//si l'element est plus grand que tout les autres
			if(!insertion){
				resultat.add(element);
				
			}
		}
		return resultat;
	}
	private TriInsertion(){
		
	}
	
}