/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 14 10:50:35 CET 2018
*
*/
import java.util.*;
public abstract class Unite implements Iterable<Unite>{
	public void accept(Visitor v){
		return;
	}
	public Iterator<Unite> iterator(){
		return null;
	}

}