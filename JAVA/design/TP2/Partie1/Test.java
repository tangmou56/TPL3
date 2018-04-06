/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 09:41:24 CET 2018
*
*/
import java.util.*;
public class Test {
	public static void main(String[] args){
		Fichier f1=new Fichier("f",5,"s");
		Fichier f2=new Fichier("f",10,"s");
		Fichier f3=new Fichier("f",8,"s");

		SystemeFichier sf=new SystemeFichier();
		sf.add(f1);
		sf.add(f2);
		sf.add(f3);
		Iterator i=sf.iterator();
		int max=0;
		Fichier fmax=null;
		while(i.hasNext()){
			Fichier f=(Fichier)i.next();
			if (f.taille>max){
				max=f.taille;
				fmax=f;
			}
		}

		System.out.println(fmax.taille);
	}
	
}