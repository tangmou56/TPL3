#include "Outil.h"
#include "Tp1.h"
//td
//(3)
//	S->abQ
//	Q->bQ+b
//(4)
//	S->U+T+a
//	T->ab
//	U->abQ
//	Q->b+bQ

//tp
//(3)
//	S->A.B.Q
//	Q->U+B
//	U->B.Q
//(4)
//	S->U+T+A
//	T->A.B
//	U->A.B.Q
//	Q->V+B
//	V->B.Q
//	A->a
//	B->b
char *sMOT;
int bTp1AmorceR=kF;
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bT(int iDebut,int *piFin);

void Tp1AMORCER(){
	bTp1AmorceR=kV;
}

void Tp1INITIALISER(){
	Assert1("Tp1INITIALISER",bTp1AmorceR);
}

void Tp1TESTER(int iTest){
	int bEngendre,iFin,bSucces;
	Assert1("Tp1TESTER0",bTp1AmorceR);
	switch(iTest){
		case 1: sMOT="abb";break;
		case 2: sMOT="abbb";break;
		case 3: sMOT="a";break;
		default:Assert1("Tp1TESTER1",0);break;

	}

	bSucces=bS(0,&iFin);
	bEngendre=bSucces&&nChaineLg(sMOT)==iFin;
	printf("%s:%s %s engendré par la Tp1 décrite dans \"Tp1.c\".\n",(bEngendre)?"SUCCES":"ECHEC",sG(sMOT),sEst(bEngendre));
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
//	S->A.B.Q
	int iFin,iX,iY;
	int bSucces=bA(iDebut,&iX)&&bB(iX,&iY)&&(d2(iX,iY),1)&&bQ(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bQ(int iDebut,int *piFin){
//	Q->U+B
	int iFin=0;
	int bSucces=bU(iDebut,&iFin)||bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);
}



int bU(int iDebut,int *piFin){
//	U->B.Q
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bQ(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}



