/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 14:27:08 CET 2018
*
*/
public class FabriqueDeCanards implements FabriqueAbstraite{

	public Cancaneur creerOie(){
		return new OieAdap(new Oie());
	}

	public Cancaneur creerAppeau(){
		return new Appeau();
	}
	public Cancaneur creerCanardEnPlastique(){
		return new CanardEnPlastique();
	}
	public Cancaneur creerColvert(){
		return new Colvert();
	}
	public Cancaneur creerMandarin(){
		return new Mandarin();
	}

	public Cancaneur ajouterBegaiement(Cancaneur c){
		return new Begue(c);
	}
	
}