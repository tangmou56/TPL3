/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 26 13:57:42 CET 2018
*
*/
public class OieAdap implements Cancaneur {
	private Oie oie;

	public  OieAdap( Oie o){
		this.oie=o;
	}
	public void cancaner(){
		oie.cacarder();
	}
}