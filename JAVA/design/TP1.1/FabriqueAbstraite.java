/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 14:25:11 CET 2018
*
*/
public interface FabriqueAbstraite {

	public Cancaneur creerOie();
	public Cancaneur creerAppeau();
	public Cancaneur creerCanardEnPlastique();
	public Cancaneur creerColvert();
	public Cancaneur creerMandarin();
	public Cancaneur ajouterBegaiement(Cancaneur c);
	
}