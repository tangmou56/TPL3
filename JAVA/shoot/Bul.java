/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Feb 22 16:47:39 CET 2018
*
*/
import java.util.*;
public class Bul {
	public int x;
	public int y;
	protected int vx;
	protected int vy;
	public int r;
	public int sb;
	private int tickx=0;
	private int ticky=0;
	public Bul(int x,int y,int vx,int vy,int r){
  		Random random = new Random();
		this.x=x;
		this.y=y;
		this.vx=vx;
		this.vy=vy;
		this.r=r;
		sb=random.nextInt(62);
	}



	public boolean roule(int w,int h){
		if(x-r>w)
			return false;
		if(x<-r)
			return false;
		if(y-r>h)
			return false;
		if(y<-r)
			return false;
		x=x+vx();
		y=y+vy();

			
		return true;
	}

	public int vx(){
		int res;
		tickx=tickx+vx;
		res=tickx/10;
		tickx=tickx%10;
		return res;
			
	}

	public int vy(){
		int res;
		ticky=ticky+vy;
		res=ticky/10;
		ticky=ticky%10;
		return res;
	}


	
}