/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 14:30:35 CET 2018
*
*/
public class FabriqueDeComptage implements FabriqueAbstraite{

	public Cancaneur creerOie(){
		return  new CompteurDeCancans(new OieAdap(new Oie()));
	}

	public Cancaneur creerAppeau(){
		return new CompteurDeCancans(new Appeau());
	}
	public Cancaneur creerCanardEnPlastique(){
		return new CompteurDeCancans(new CanardEnPlastique());
	}
	public Cancaneur creerColvert(){
		return new CompteurDeCancans(new Colvert());
	}
	public Cancaneur creerMandarin(){
		return new CompteurDeCancans(new Mandarin());
	}

	public Cancaneur ajouterBegaiement(Cancaneur c){
		return new Begue(c);
	}
	
}