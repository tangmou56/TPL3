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
/*char *sMOT;
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
		case 4: sMOT="";break;
		case 5: sMOT="asq";break;
		case 6: sMOT="baba";break;
		case 7: sMOT="abba";break;
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
	int bSucces=bA(iDebut,&iX)&&bB(iX,&iY)&&bQ(iY,&iFin);
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
*/



//TP2
//(1)
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
//S->W+U+V
//U->M+N
//M->B.U
//N->B.A
//W->B.X.B
//X->Z+A
//Z->A.X
//V->B.B

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

//(3)
//langage
//L=  ba + b(n)a(n)(b*)a,n>=0
//L=  ba + (1+(b+))a + b(n)a(n)(1+(b+))a,n>0
//L=  b(n)a(n)(b+)a + b(n)a(n)a + (b+)a + ba + a  ,n>0 

//Grammaire algebrique
//S->Ua+Va+Wa+ba+a
//U->U1U2
//U1->bU1a+ba
//U2->b+bU2
//V->bVa+ba
//W->bW+b

//Grammaire homogene
//S->U+V+W+X+A
//U->U1.A
//U1->U3.U4
//U3->U5+U6
//U4->U7+B
//U5->B.U3.A
//U6->B.A
//U7->B.U4
//V->V1.A
//V1->V2+V3
//V2->B.V1.A
//V3->B.A
//W->W1.A
//W1->W2+B
//W2->B.W1
//X->B.A