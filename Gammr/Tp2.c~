#include "Outil.h"
#include "Tp2.h"
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
		case 5: sMOT="bbbaaaa";break;
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
//S->U+V+W+X+A


	int iFin;
	int bSucces=bU(iDebut,&iFin)||bV(iDebut,&iFin)||bW(iDebut,&iFin)||bX(iDebut,&iFin)||bA(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bU(int iDebut,int *piFin){
//U->U1.A
	int iX,iFin=0;
	int bSucces=bU1(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);
}



int bU1(int iDebut,int *piFin){
//U1->U3.U4
	int iX,iFin;
	int bSucces=bU3(iDebut,&iX)&&bU4(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bU3(int iDebut,int *piFin){
//U3->U5+U6
	int iFin;
	int bSucces=bU5(iDebut,&iFin)||bU6(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bU4(int iDebut,int *piFin){
//U4->U7+B
	int iFin;
	int bSucces=bU7(iDebut,&iFin)||bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bU5(int iDebut,int *piFin){
//U5->B.U3.A
	int iX,iY,iFin;
	int bSucces=bB(iDebut,&iX)&&bU3(iX,&iY)&&bA(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bU6(int iDebut,int *piFin){
//U6->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}


int bU7(int iDebut,int *piFin){
//U7->B.U4
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bU4(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bV(int iDebut,int *piFin){
//V->V1.A
	int iX,iFin;
	int bSucces=bV1(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bV1(int iDebut,int *piFin){
//V1->V2+V3
	int iFin;
	int bSucces=bV2(iDebut,&iFin)||bV3(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bV2(int iDebut,int *piFin){
//V2->B.V1.A
	int iX,iY,iFin;
	int bSucces=bB(iDebut,&iX)&&bV1(iX,&iY)&&bA(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bV3(int iDebut,int *piFin){
//V3->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bW(int iDebut,int *piFin){
//W->W1.A
	int iX,iFin;
	int bSucces=bW1(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bW1(int iDebut,int *piFin){
//W1->W2+B
	int iFin;
	int bSucces=bW2(iDebut,&iFin)||bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}

int bW2(int iDebut,int *piFin){
//W2->B.W1
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bW1(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
int bX(int iDebut,int *piFin){
//X->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	return (bSucces);

}
