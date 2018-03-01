/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Feb 22 17:33:34 CET 2018
*
*/
public class Bul2 extends Bul{
	public Bul2(int x,int y,int vx,int vy,int r){
		super(x,y,vx,vy,r);
	}


	
	public boolean roule(int w,int h){
		if(x+r>w)
			vx=-vx;
		if(x<0)
			vx=-vx;
		if(y>h-r)
			vy=-vy;
		if(y<0)
			vy=-vy;
		x=x+vx();
		y=y+vy();

			
		return true;
	}


	
}