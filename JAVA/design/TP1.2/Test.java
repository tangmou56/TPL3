/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 15:27:38 CET 2018
*
*/
import java.util.LinkedList;
public class Test {
	
	public static void main(String[] args){
	System.out.println("Test bdd");
		LinkedList<BaseDeDonnees<String>> lstBdd= new LinkedList<BaseDeDonnees<String>>();
		lstBdd.add(new BaseDeDonnees<String>(TriJava.getInstance()));
		lstBdd.add(new BaseDeDonnees<String>(TriBulle.getInstance()));
		lstBdd.add(new BaseDeDonnees<String>(TriInsertion.getInstance()));

		for(BaseDeDonnees<String> bdd :lstBdd){
			bdd.ajouter("1");
			bdd.ajouter("2");
			bdd.ajouter("3");
			bdd.ajouter("4");
			bdd.ajouter("5");
			bdd.ajouter("6");
			bdd.ajouter("7");
		}
		for(BaseDeDonnees<String> bdd :lstBdd){
			bdd.afficheDonneesTriees();
			System.out.println();
		}
		
	}
		
		
}
