#include "Outil.h"
#include "Tp2.h"
//langage
//L=b(b*a+a*b)
//L=bb*a+ba*b
//L=(b+)a   + b(1+(a+))b
//L=(b+)a  +  b(a+)b   +  bb
//Grammaire algebrique
//S->U+bVb+bb
//U->bU+ba
//V->aV+a
//Grammaire homogene
//S->U+W+V
//U->M+N
//M->B.U
//N->B.A
//W->B.X.B
//X->Z+A
//Z->A.X
//V->B.B

char *sMOT;
int bTp2AmorceR=kF;
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bT(int iDebut,int *piFin);

void Tp2AMORCER(){
	bTp2AmorceR=kV;
}

void Tp2INITIALISER(){
	Assert1("Tp2INITIALISER",bTp2AmorceR);
}

void Tp2TESTER(int iTest){
	int bEngendre,iFin,bSucces;
	Assert1("Tp2TESTER0",bTp2AmorceR);
	switch(iTest){
		case 1: sMOT="bbbba";break;
		case 2: sMOT="baaaaaaab";break;
		case 3: sMOT="bb";break;
		case 4: sMOT="";break;
		case 5: sMOT="asq";break;
		case 6: sMOT="baba";break;
		case 7: sMOT="abba";break;
		default:Assert1("Tp2TESTER1",0);break;

	}

	bSucces=bS(0,&iFin);
	bEngendre=bSucces&&nChaineLg(sMOT)==iFin;
	printf("%s:%s %s engendré par la Tp2 décrite dans \"Tp2.c\".\n",(bEngendre)?"SUCCES":"ECHEC",sG(sMOT),sEst(bEngendre));
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
//S->W+U+V
	int iFin;
	int bSucces=bW(iDebut,&iFin)||bU(iDebut,&iFin)||bV(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bU(int iDebut,int *piFin){
//U->M+N
	int iFin=0;
	int bSucces=bM(iDebut,&iFin)||bN(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);
}



int bM(int iDebut,int *piFin){
//M->B.U
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bU(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bN(int iDebut,int *piFin){
//N->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bW(int iDebut,int *piFin){
//W->B.X.B
	int iX,iY,iFin;
	int bSucces=bB(iDebut,&iX)&&bX(iX,&iY)&&bB(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bX(int iDebut,int *piFin){
//X->Z+A
	int iFin;
	int bSucces=bZ(iDebut,&iFin)||bA(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bZ(int iDebut,int *piFin){
//Z->A.X
	int iX,iFin;
	int bSucces=bA(iDebut,&iX)&&bX(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bV(int iDebut,int *piFin){
//V->B.B
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bB(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
