/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 11:15:03 CET 2018
*
*/
public interface Visitor {
	public void visite(Repertoire r);
	public void visite(Fichier f);
}