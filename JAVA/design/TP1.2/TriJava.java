/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 15:22:20 CET 2018
*
*/
import java.util.List;
import java.util.Collections;
public class TriJava implements StrategieTri{

	private static TriJava tri=null;

	public static TriJava getInstance(){
		if(tri==null){
			tri=new TriJava();
		}
		return tri;
	}
	public <T extends Comparable<T>>  List<T> trie(List<T> donnees){
		Collections.sort(donnees);
		return donnees;
	}
	private TriJava(){
		
	}
}