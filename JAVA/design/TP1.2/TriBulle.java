/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 15:10:54 CET 2018
*
*/
import java.util.List;
import java.util.Collections;
public class TriBulle implements StrategieTri {

	private static TriBulle tri=null;

	public static TriBulle getInstance(){
		if(tri==null){
			tri=new TriBulle();
		}
		return tri;
	}
	public <T extends Comparable<T>> List<T> trie(List<T> donnees){

		boolean echange;
		int i,butee=1;

		do{

			for(i=0,echange=false;i<(donnees.size()-butee);i++){
				if(donnees.get(i).compareTo(donnees.get(i+1)) >0){
					Collections.swap(donnees,i,i+1);
					echange=true;
					break;
				}
			}
			butee++;
		}while(echange !=false);
		return donnees;
	}
	private TriBulle(){
		
	}
	
}