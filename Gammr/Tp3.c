#include "Outil.h"
#include "Tp3.h"

//langage
//L=((a+b)+)


//Grammaire algébrique
//S->aS+bS+a+b



//Grammaire homogène
//S->T
//T->T1+T2+A+B
//T1->A.T
//T2->B.T

//Attribut
//S(a,b)->T(a,b)
//T(a,b)->T1(a,b)+T2(a,b)+T3(a,b)+T4(a,b)
//T1(a+1,b)->A.T(a,b)
//T2(a,b+1)->B.T(a,b)
//T3(1,0)->A
//T4(0,1)->B

char *sMOT;
int bTp2AmorceR=kF;
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bS(int iDebut,int *piFin,int *paA,int *paB);


void Tp3AMORCER(){
	bTp2AmorceR=kV;
}

void Tp3INITIALISER(){
	Assert1("Tp2INITIALISER",bTp2AmorceR);
}

void Tp3TESTER(int iTest){
	int bEngendre,iFin,bSucces,a,b;
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

	bSucces=bS(0,&iFin,&a,&b);
	bEngendre=bSucces&&nChaineLg(sMOT)==iFin;
	printf("%s:%s %s engendré par la Tp3 décrite dans \"Tp3.c\".\n",(bEngendre)?"SUCCES":"ECHEC",sG(sMOT),sEst(bEngendre));
	if(bEngendre)
		printf("Nombre a=%i,Nombre b=%i\n",a,b);

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

int bS(int iDebut,int *piFin,int *paA,int *paB){
//S(a,b)->T(a,b)






	int iFin,aA,aB;
	int bSucces=bT(iDebut,&iFin,&aA,&aB);

	*piFin=(bSucces)?iFin:iDebut;
	*paA=aA;
	*paB=aB;
	return (bSucces);

}




int bT(int iDebut,int *piFin,int *paA,int *paB){
//T(a,b)->T1(a,b)+T2(a,b)+T3(a,b)+T4(a,b)
	int iFin=0,aA,aB;
	int bSucces=bT1(iDebut,&iFin,&aA,&aB)||bT2(iDebut,&iFin,&aA,&aB)||bT3(iDebut,&iFin,&aA,&aB)||bT4(iDebut,&iFin,&aA,&aB);
	*piFin=(bSucces)?iFin:iDebut;
	*paA=aA;
	*paB=aB;
	return (bSucces);
}



int bT1(int iDebut,int *piFin,int *paA,int *paB){
//T1(a+1,b)->A.T(a,b)
	int iX,iFin,aA,aB;
	int bSucces=bA(iDebut,&iX)&&bT(iX,&iFin,&aA,&aB);
	*piFin=(bSucces)?iFin:iDebut;
	*paA=aA+1;
	*paB=aB;
	return (bSucces);

}




int bT2(int iDebut,int *piFin,int *paA,int *paB){
//T2(a,b+1)->B.T(a,b)
	int iX,iFin,aA,aB;
	int bSucces=bB(iDebut,&iX)&&bT(iX,&iFin,&aA,&aB);
	*piFin=(bSucces)?iFin:iDebut;
	*paA=aA;
	*paB=aB+1;
	return (bSucces);

}


int bT3(int iDebut,int *piFin,int *paA,int *paB){
//T3(1,0)->A
	int iFin;
	int bSucces=bA(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paA=1;
	*paB=0;
	return (bSucces);

}

int bT4(int iDebut,int *piFin,int *paA,int *paB){
//T4(0,1)->B
	int iFin;
	int bSucces=bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paA=0;
	*paB=1;
	return (bSucces);

}