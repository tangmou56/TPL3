/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 09:07:42 CET 2018
*
*/
import java.util.*;
public class Fichier extends Unite{
	public String nom;
	public int taille;
	public String contenu;
	public Date date;

	public Fichier(String nom,int taille,String contenu){
		this.nom=nom;
		this.taille=taille;
		this.contenu=contenu;
		date=new Date();
	}


	public Iterator<Unite> iterator(){
		return new IterateurSystemeFichier(new ArrayList<Unite>());
	}


	public void accept(Visitor v){
		v.visite(this);
	}



}