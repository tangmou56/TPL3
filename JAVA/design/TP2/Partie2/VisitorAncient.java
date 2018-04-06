/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 11:03:55 CET 2018
*
*/
import java.util.*;
public class VisitorAncient implements Visitor{
	
	private Date min=null;
	private Fichier fmin;
	public void visite(Repertoire r){
		System.out.println("le plus ancient fichier dans "+r.nom);
		Iterator i=r.iterator();
		while(i.hasNext()){
			Unite u=(Unite)i.next();
			if(u instanceof Fichier){
				Fichier f=(Fichier)u;
				if(min==null){
					min=f.date;
					fmin=f;
				}
				else{
					if(min.after(f.date)){
						min=f.date;
						fmin=f;
					}
					
				}
			}
			
		}
		System.out.println(fmin.nom);
	}

	public void visite(Fichier f){
		return ;
	}
}