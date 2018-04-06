/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 10:45:52 CET 2018
*
*/
import java.util.*;
public class VisitorParcourir implements Visitor{
	public void visite(Repertoire r){
		System.out.println(r.nom+" contient:");
		Iterator i=r.iterator();
		while(i.hasNext()){
			Unite u=(Unite)i.next();
			if(u instanceof Fichier){
				Fichier f=(Fichier)u;
				System.out.println(f.nom);
			}
			else{
				Repertoire rn=(Repertoire)u;
				System.out.println(rn.nom);
			}
		}
	}


	public void visite(Fichier f){
		System.out.println(f.contenu);
	}
}