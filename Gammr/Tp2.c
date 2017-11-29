#include "Outil.h"
#include "Tp2.h"

//(2)
//langage
//L=b(n)a(n)b,n>=0
//L=  (1+b(n)) . (1+a(n)) . b ,n>0
//L=   a(n=0)b + b(n=0)b + b(n)a(n)b  +  b , n>0
//L=   b + b(n)a(n)b,n>0
//Grammaire algebrique
//S->Wb+b
//W->bWa+ba
//Grammaire homogene
//S->W+B
//W->W1.B
//W1->W2+W3
//W2->B.W1.A
//W3->B.A
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
		case 5: sMOT="bbbaaab";break;
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
//S->W+B
	int iFin;
	int bSucces=bW(iDebut,&iFin)||bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bW(int iDebut,int *piFin){
//W->W1.B
	int iX,iFin=0;
	int bSucces=bW1(iDebut,&iX)&&bB(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);
}



int bW1(int iDebut,int *piFin){
//W1->W2+W3
	int iFin;
	int bSucces=bW2(iDebut,&iFin)||bW3(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bW2(int iDebut,int *piFin){
//W2->B.W1.A
	int iX,iY,iFin;
	int bSucces=bB(iDebut,&iX)&&bW1(iX,&iY)&&bA(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bW3(int iDebut,int *piFin){
//W3->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

