/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 10:04:27 CET 2018
*
*/
import java.util.*;
public class Repertoire extends Unite{
	List<Unite> list=new ArrayList<Unite>();
	public String nom;
	public Iterator<Unite> iterator(){
		return new IterateurSystemeFichier(list);
	}
	public Repertoire(String nom){
		this.nom=nom;
	}

	public void add(Unite u){
		list.add(u);
	}

	public void remove(Unite u){
		list.remove(u);
	}

	public void accept(Visitor v){
		v.visite(this);
	}

}