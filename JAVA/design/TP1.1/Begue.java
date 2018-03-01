/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 14:18:24 CET 2018
*
*/
public class Begue implements Cancaneur {
	Cancaneur c;

	public Begue(Cancaneur c){
		this.c=c;
	}

	public void cancaner(){
		System.out.println("C-C-C");
	}
	
}