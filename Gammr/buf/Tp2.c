#include "Outil.h"
#include "Graphe.h"
#include "Tp2.h"
#define kuSommetMax 100
int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER


void DistancierAvecFloyD(graf *pgSimple,int nDist[][1+kuSommetMax],int *pnComplexiteh){//(O(S3)
	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgSimple->coulh[]
	int i,j,K,I,J;
	int aK,sX,sY;//a comme arc;s comme sommet
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgSimple->nSommetEnTout;
	int dM[1+nSommet][1+nSommet];//matrice des distances,supposées être des entiers ou des réels déjà ramenés à des entiers
	int D[1+nSommet][1+nSommet];
	int P[1+nSommet][1+nSommet];
	*pnComplexiteh=0;
	for(i=1;i<=nSommet;i++){
		for(j=1;j<=nSommet;j++){
			D[i][j]=100000;
			P[i][j]=0;
			*pnComplexiteh=*pnComplexiteh+1;
		}
	}

	Assert1("DistancierCalculeR",bGrapheSimple(pgSimple));
	//générer la matrice d'incidence sommet-sommet dM qui décrit le graphe simple pgSimple
		//dM:=0
			for (uL=1;uL<=nSommet;uL++)
				for (uC=1;uC<=nSommet;uC++){
					dM[uL][uC]=0;
					*pnComplexiteh=*pnComplexiteh+1;			
				}
		for (sX=1;sX<=nSommet;sX++)
			for (aK=pgSimple->aHed[sX];aK<pgSimple->aHed[sX+1];aK++){
				*pnComplexiteh=*pnComplexiteh+1;
				sY=pgSimple->sSuk[aK];
				dM[sX][sY]=pgSimple->coulh[aK];//distance (sX,sY)
			}
	//exécuter l'algorithme de Floyd sur dM
		//code à compléter...
		for(sX=1;sX<=nSommet;sX++){
			P[sX][sX]=0;
			for(sY=1;sY<=nSommet;sY++){
				*pnComplexiteh=*pnComplexiteh+1;
				if(dM[sX][sY]!=0){
					D[sX][sY]=dM[sX][sY];
					P[sX][sY]=sX;			
				}			
			}
		}
		for(K=1;K<=nSommet;K++){
			for(I=1;I<=nSommet;I++){
				for(J=1;J<=nSommet;J++){
					*pnComplexiteh=*pnComplexiteh+1;
					if(D[I][J]>D[I][K]+D[K][J]){
						D[I][J]=D[I][K]+D[K][J];
						P[I][J]=P[K][J];		
					}
				}	
			}
	
		}

		for(sX=1;sX<=nSommet;sX++){
			for(sY=1;sY<=nSommet;sY++){
				nDist[sX][sY]=D[sX][sY];
			}
		}
		
		for(sX=1;sX<=nSommet;sX++)
			nDist[sX][sX]=0;
		
	
}//DistancierCalculeR

void DistancierAvecDijkstrA(graf *pgG,int sSource,int nDyst[1+kuSommetMax],int *pnComplexiteh){
	int aX,sX,i,j;
	int narc=pgG->nArcEnTout;
	int nSommet=pgG->nSommetEnTout;
	int complex=0;
	for(aX=1;aX<=narc;aX++){
		pgG->nCout[aX]=pgG->coulh[aX];
		*pnComplexiteh=*pnComplexiteh+1;
	}

	for(sX=1;sX<=nSommet;sX++){		
		nDyst[sX]=bGrapheCheminerCourt(pgG,sSource,sX,0,&complex);
		*pnComplexiteh=*pnComplexiteh+1+complex;
		
	}

	


	//calculer le distancier de pgG supposé peu dense (algo de Dijkstra avec tas)
}//Tp1Distancier


int nDistancierCalculeR(graf *pgG,int nSommet,int bFloydSinonDijkstra,int bAfficher){
	int nDist[1+kuSommetMax][1+kuSommetMax];
	int nDyst[1+kuSommetMax];
	int complex=0,comp2=0;
	int i,j;
	for(i=1;i<=nSommet;i++){
		for(j=1;j<=nSommet;j++){
			nDist[i][j]=100000;
		}
	}

	if(bFloydSinonDijkstra){
		printf("Distancier par floyd\n");
		DistancierAvecFloyD(pgG,nDist,&complex);
		

	}
	else{
		printf("Distancier par Dijkstra\n");
		for(i=1;i<=nSommet;i++){
			
			comp2=0;
			DistancierAvecDijkstrA(pgG,i,nDyst,&comp2);
			complex=complex+comp2;
			for(j=1;j<=nSommet;j++){
				nDist[i][j]=nDyst[j];
			}
		}





	}

	if(bAfficher){
		printf("  ");
		for(i=1;i<=nSommet;i++)
			printf(" %i ",i);
		printf("\n");
		for(i=1;i<=nSommet;i++){
			printf("%i ",i);
			for(j=1;j<=nSommet;j++){
				if(nDist[i][j]==100000)
					printf(" X ",nDist[i][j]);
				else
					printf(" %i ",nDist[i][j]);
			}
			printf("\n");
		}
		printf("Le complexité est %i\n",complex);
	}
	return complex;


}


void PerformanceComparR(int nGrapheEnTout){
	int i;
	int complexd,complexf;	
	graf *pgG;
	for(i=1;i<nGrapheEnTout;i++){
		
		GrapheAllouerInitialiseR(i,-1,&pgG);
		printf("Graphe %i  :\n",i);
		complexf=nDistancierCalculeR(pgG,pgG->nSommetEnTout,1,0);
		complexd=nDistancierCalculeR(pgG,pgG->nSommetEnTout,0,0);
		printf("Complexité par floyd : %i,Complexité par dijkstra : %i \n\n",complexf,complexd);

	}



}










void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp2AmorceR,!bTp2OuverT);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	int pnComplexiteh=0;
	int nDist[1+kuSommetMax][1+kuSommetMax];
	int nDyst[1+kuSommetMax];
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			GrapheCreer(0,&pgG);
			break;
		case 2: //calcule complexité floyed
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			DistancierAvecFloyD(pgG,nDist,&pnComplexiteh);
			break;
		case 3: //calcule complexité dijkstra
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			DistancierAvecDijkstrA(pgG,1,nDyst,&pnComplexiteh);
			break;
		case 4: //calcule complexité floyed et dijkstra
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			nDistancierCalculeR(pgG,pgG->nSommetEnTout,1,1);
			nDistancierCalculeR(pgG,pgG->nSommetEnTout,0,1);
			break;
		case 5: //calcule complexité floyed
			PerformanceComparR(4);
			break;
		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	

