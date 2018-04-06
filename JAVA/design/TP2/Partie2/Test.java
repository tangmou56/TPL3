/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 11:11:10 CET 2018
*
*/
import java.util.*;
public class Test {
	public static void main(String[] args){
		Fichier f1=new Fichier("f1",5,"s1");
		try {
      		Thread.sleep(1000); 
      	}catch (InterruptedException e) {
      		return;
     	}
		Fichier f2=new Fichier("f2",10,"s2");
		Fichier f3=new Fichier("f3",8,"s3");
		Fichier f4=new Fichier("f4",25,"s4");
		Repertoire sf=new Repertoire("r1");
		Repertoire sf2=new Repertoire("r2");
		sf2.add(f4);
		sf.add(f1);
		sf.add(f2);
		sf.add(f3);
		sf.add(sf2);
		sf.accept(new VisitorParcourir());
		
		sf.accept(new VisitorAncient());
	}
}