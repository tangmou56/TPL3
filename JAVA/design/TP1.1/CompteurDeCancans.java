/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 14:11:02 CET 2018
*
*/
public class CompteurDeCancans implements Cancaneur {
	private static int nbCancans = 0;

	Cancaneur c;

	public CompteurDeCancans(Cancaneur c){
		this.c=c;

		nbCancans++;
	}
	public void cancaner(){
		c.cancaner();
	}

	public static int getNbCancans(){
		return nbCancans;
	}
	public static void setNbCancans(int nb){
		nbCancans=nb;
	}
	
}