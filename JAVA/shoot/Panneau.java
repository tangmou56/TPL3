
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
public class Panneau extends JPanel {

  private int posX = -50;
  private int posY = -50;
  private int r=50;
  private ArrayList<Bul> lo=new ArrayList<Bul>();
	public Panneau(){
		addKeyListener( new KeyAdapter(){
			public void keyPressed(KeyEvent e){
				switch(e.getKeyCode()){
					case KeyEvent.VK_DOWN: posY += 10; break;
					case KeyEvent.VK_UP: posY -= 10; break;
					case KeyEvent.VK_LEFT: posX -= 10; break;
					case KeyEvent.VK_RIGHT: posX += 10;break;
					case KeyEvent.VK_SPACE: addB(posX+r/2,posY+r/2,1,1,5);
											addB(posX+r/2,posY+r/2,-1,1,5); 
											addB(posX+r/2,posY+r/2,1,-1,5);
											addB2(posX+r/2,posY+r/2,-1,-2,20);
											addB(posX+r/2,posY+r/2,0,1,5);
											addB(posX+r/2,posY+r/2,1,0,5);
											addB2(posX+r/2,posY+r/2,-1,0,10);
											addB(posX+r/2,posY+r/2,0,-1,5);
											break;
					//default: KeyChar = e.getKeyChar();
				}
        
			}
			
		});
		setFocusable(true);
		
	}



  public void paintComponent(Graphics g) {
  	int w=this.getWidth();
  	int h=this.getHeight();
  	String str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  	Bul ob;
    // On décide d'une couleur de fond pour notre rectangle
    g.setColor(Color.white);
    // On dessine celui-ci afin qu'il prenne tout la surface
    g.fillRect(0, 0, this.getWidth(), this.getHeight());
    // On redéfinit une couleur pour notre rond
    g.setColor(Color.red);
    // On le dessine aux coordonnées souhaitées
    if(posX>this.getWidth()-r){
		posX=this.getWidth()-r;
	}
	if(posX<0){
		posX=0;
	}
	if(posY>this.getHeight()-r)
		posY=this.getHeight()-r;
	if(posY<0)
		posY=0;
	
    g.fillOval(posX, posY, r, r);
	for(int i=0,len=lo.size();i<len;i++){
		
		ob=lo.get(i);
		if(!ob.roule(w,h)){
			lo.remove(i);
			len-=1;
		}
		else{
			g.setFont( new Font("TimesRoman" ,Font.PLAIN,ob.r));
			g.drawString(String.valueOf(str.charAt(ob.sb)),ob.x,ob.y);
			//g.fillOval(ob.x, ob.y, ob.r, ob.r);	
		}
	}
	
	
    
  }

  public int getPosX() {
    return posX;
  }

  public void setPosX(int posX) {
    this.posX = posX;
  }

  public int getPosY() {
    return posY;
  }

  public void setPosY(int posY) {
    this.posY = posY;
  }

  public void addB(int x,int y,int vx,int vy,int r){
  	lo.add(new Bul(x,y,vx,vy,r));	
  }
  public void addB2(int x,int y,int vx,int vy,int r){
  	lo.add(new Bul2(x,y,vx,vy,r));	
  }



  
}