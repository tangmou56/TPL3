#include "Outil.h"
#include "Tp3.h"

//langage
//L=b(n)a(n),n est un carre non nul


//Grammaire algébrique
//S->T
//T->bTa+ba


//Grammaire homogène
//S->T
//T->T1+T2
//T1->B.T.A
//T2->B.A

//Attribut
//S->T(a).(a est un carre non nul)
//T(a)->T1(a)+T2(a)
//T1(a+1)->B.T(a).A
//T2(1)->B.A


char *sMOT;
int bTp2AmorceR=kF;
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);


void Tp3AMORCER(){
	bTp2AmorceR=kV;
}

void Tp3INITIALISER(){
	Assert1("Tp2INITIALISER",bTp2AmorceR);
}

void Tp3TESTER(int iTest){
	int bEngendre,iFin,bSucces;
	Assert1("Tp3TESTER0",bTp2AmorceR);
	switch(iTest){
		case 1: sMOT="bbbbaaaa";break;
		case 2: sMOT="baaaaaaab";break;
		case 3: sMOT="ba";break;
		case 4: sMOT="";break;
		case 5: sMOT="bbbaaabbb";break;
		case 6: sMOT="bab";break;
		case 7: sMOT="bbaabbb";break;
		default:Assert1("Tp2TESTER1",0);break;

	}

	bSucces=bS(0,&iFin);
	bEngendre=bSucces&&nChaineLg(sMOT)==iFin;
	printf("%s:%s %s engendré par la Tp3 décrite dans \"Tp3.c\".\n",(bEngendre)?"SUCCES":"ECHEC",sG(sMOT),sEst(bEngendre));
}


int bA(int iDebut,int *piFin){
	int bSucces=sMOT[iDebut]=='a';
	*piFin=(bSucces)?iDebut+1:iDebut;
	return (bSucces);

}

int bB(int iDebut,int *piFin){
	int bSucces=sMOT[iDebut]=='b';
	*piFin=(bSucces)?iDebut+1:iDebut;
	return (bSucces);

}

int bS(int iDebut,int *piFin){
//S->T(a).(a est un carre non nul)




	int iFin,aT;
	int bSucces=bT(iDebut,&iFin,&aT)&&(estcarre(aT));

	*piFin=(bSucces)?iFin:iDebut;
	
	return (bSucces);

}

int puss(int n){
	int i,res=1;
	for(i=0;i<n;i++){
		 	res=res*2;
		
		}
	return res;

}



int estcarre(int n){
		int i,a=0;
		for(i=0;i<10;i++){
				if(n==puss(i))			
						a= 1;
			}

	return a;
	}



int bT(int iDebut,int *piFin,int *paN){
//T(a)->T1(a)+T2(a)
	int iFin=0,aT;
	int bSucces=bT1(iDebut,&iFin,&aT)||bT2(iDebut,&iFin,&aT);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=aT;
	return (bSucces);
}



int bT1(int iDebut,int *piFin,int *paN){
//T1(a+1)->B.T(a).A
	int iX,iY,iFin,aT;
	int bSucces=bB(iDebut,&iX)&&bT(iX,&iY,&aT)&&bA(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=aT+1;
	return (bSucces);

}




int bT2(int iDebut,int *piFin,int *paN){
//T2(1)->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=1;
	return (bSucces);

}

