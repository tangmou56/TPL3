/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 14:48:37 CET 2018
*
*/
import java.util.List;
import java.util.LinkedList;
public class TroupeDeCancaneurs implements Cancaneur{

	private List<Cancaneur> cancaneurs;

	public TroupeDeCancaneurs(){
		cancaneurs = new LinkedList<Cancaneur>();
	}

	public void ajouter(Cancaneur c){
		cancaneurs.add(c);
	}

	public void supprimer(Cancaneur c){
		cancaneurs.remove(c);
	}

	public void cancaner(){
		for(Cancaneur c: cancaneurs){
			c.cancaner();
		}
	}
	
}