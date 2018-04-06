/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 09:17:20 CET 2018
*
*/
import java.util.*;
public class SystemeFichier implements Iterable<Fichier>{
	private List<Fichier> list=new ArrayList<Fichier>();

	public Iterator<Fichier> iterator(){
		return new IterateurSystemeFichier(list);
	}


	public void add(Fichier f){
		list.add(f);
	}
	
}