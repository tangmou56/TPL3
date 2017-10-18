#include "Outil.h"
#include "Graphe.h"
#include "Tp3.h"

int bTp3AmorceR;//ie le module a effectivement été amorcé
int bTp3OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
	bTp3OuverT=kF;
}//Tp3AMORCER

void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp3AmorceR,!bTp3OuverT);
}//Tp3INITIALISER



void TP3Facturer(int sOrigine,int sDestination,int nLongueur,int nLargeur,int nHauteur){
	int aX,km=0,complex,nlon,nlar,nhau;
	graf  *pgg;
	char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char hauteur[]="AE4BE3EF3FC2FD3GA8GB8CH9DH9";
	char longueur[]="AE9BE3EF3FC2FD3GA8GB8CH9DH9";
	char largeur[]="AE9BE3EF5FC2FD3GA8GB8CH9DH9";


	GrapheGenerer(ksPetit,&pgg);//le champ coulh est la distance
	int narc=pgg->nArcEnTout;

	for(aX=1;aX<=narc;aX++){
		pgg->nCout[aX]=pgg->coulh[aX];
		nhau=hauteur[3*aX-1]-'0';
		nlar=largeur[3*aX-1]-'0';
		nlon=longueur[3*aX-1]-'0';
		
		if(nhau<nHauteur||nlar<nLargeur||nlon<nLongueur)
			pgg->nCout[aX]=1000;
			
			
	}

	km=bGrapheCheminerCourt(pgg,sOrigine,sDestination,0,&complex);
	if(km>=100000)
		printf("Il n'y a pas de chemin entre ces deux positions \n");
	else if(km>=1000)
		printf("Les dimensions sont incompatibles\n");
	else
 		printf(" distance en km : %i\n",km);
	
	

}


void TP3Router(int nHeure,int nMinute,int nSeconde,int sOrigine,int sDestination,int nLongueur,int nLargeur,int nHauteur){
	int time=0,n,aX,km=0,complex,nlon,nlar,nhau,sY=0,sX;
	graf  *pgg;
	char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char hauteur[]="AE4BE3EF3FC2FD3GA8GB8CH9DH9";
	char longueur[]="AE9BE3EF3FC2FD3GA8GB8CH9DH9";
	char largeur[]="AE9BE3EF5FC2FD3GA8GB8CH9DH9";
	char temps[]="AE1BE3EF1FC2FD5GA8GB8CH7DH1";
	GrapheGenerer(ksPetit,&pgg);//le champ coulh est la distance
	int narc=pgg->nArcEnTout;

	for(aX=1;aX<=narc;aX++){
		pgg->nCout[aX]=pgg->coulh[aX];
		nhau=hauteur[3*aX-1]-'0';
		nlar=largeur[3*aX-1]-'0';
		nlon=longueur[3*aX-1]-'0';
		
		if(nhau<nHauteur||nlar<nLargeur||nlon<nLongueur)
			pgg->nCout[aX]=1000;
			
			
	}
	km=bGrapheCheminerCourt(pgg,sOrigine,sDestination,0,&complex);
	sX=pgg->sPer[sDestination];
	sY=sDestination;
	while(sX!=sOrigine){
		aX=nGrapheArc(pgg,sX,sY);
		
		time=time+temps[3*aX-1]-'0';	
		sY=sX;
		sX=pgg->sPer[sX];
	}
	aX=nGrapheArc(pgg,sX,sY);
	
	time=time+temps[3*aX-1]-'0';
	printf("distance %i temps %i \n",km,time);
	
}










void Tp3TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			TP3Facturer(1,4,1,1,1);
			GrapheCreer(0,&pgG);
			break;
		case 2: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			TP3Router(10,15,0,1,6,1,1,1);
			GrapheCreer(0,&pgG);
			break;
		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

