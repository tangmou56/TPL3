/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 13:41:50 CET 2018
*
*/
public class Simulateur {
	public static void main(String[] args){
		Simulateur sim= new Simulateur();
		sim.simuler();
	}
	public void simuler(){
		Cancaneur colvert = new Begue(new CompteurDeCancans(new Colvert()));
		Cancaneur mandarin = new Begue(new CompteurDeCancans(new Mandarin()));
		Cancaneur canardEnPlastique = new Begue(new CompteurDeCancans(new CanardEnPlastique()));
		Cancaneur appeau = new Begue(new CompteurDeCancans(new Appeau()));
		Cancaneur oie= new Begue(new CompteurDeCancans(new OieAdap(new Oie())));
		
	System.out.println("Simulateur de Canards");
	simuler(colvert);
	simuler(mandarin);
	simuler(canardEnPlastique);
	simuler(appeau);
	simuler(oie);
	System.out.println("Nous avons compté "+ CompteurDeCancans.getNbCancans() + " cancans");
	System.out.println("remise a zero du compteur");
	CompteurDeCancans.setNbCancans(0);
	FabriqueDeCanards fca = new FabriqueDeCanards();
	FabriqueDeComptage fco = new FabriqueDeComptage();

	Cancaneur oie1= fca. creerOie();
	Cancaneur appeau1 = fca.creerAppeau();
	Cancaneur canardEnPlastique1= fca.creerCanardEnPlastique();
	Cancaneur colvert1= fca.creerColvert();
	Cancaneur mandarin1= fca.creerMandarin();
	System.out.println("Nous avons compté "+ CompteurDeCancans.getNbCancans() + " cancans");
	
	simuler(colvert1);
	simuler(mandarin1);
	simuler(canardEnPlastique1);
	simuler(appeau1);
	simuler(oie1);


	Cancaneur oie2= fco. creerOie();
	Cancaneur appeau2 = fco.creerAppeau();
	Cancaneur canardEnPlastique2= fco.creerCanardEnPlastique();
	Cancaneur colvert2= fco.creerColvert();
	Cancaneur mandarin2= fco.creerMandarin();
	System.out.println("Nous avons compté "+ CompteurDeCancans.getNbCancans() + " cancans");

	simuler(colvert2);
	simuler(mandarin2);
	simuler(canardEnPlastique2);
	simuler(appeau2);
	simuler(oie2);

	System.out.println("Troupe de cancaneurs");
	TroupeDeCancaneurs tc = new TroupeDeCancaneurs();

	tc.ajouter(colvert2);
	tc.ajouter(mandarin2);
	tc.ajouter(canardEnPlastique2);
	tc.ajouter(appeau2);
	tc.ajouter(oie2);

	tc.cancaner();
	}

	public void simuler(Cancaneur c){
		c.cancaner();
	}
	
}