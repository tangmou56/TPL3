/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 15:08:03 CET 2018
*
*/
import java.util.List;
public interface StrategieTri {
	
		<T extends Comparable<T>> List<T> trie(List<T> donnees);

}