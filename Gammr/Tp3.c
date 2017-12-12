#include "Outil.h"
#include "Tp3.h"

//langage
//L=b(n)a(n)b(n)
//L'=b(n)a(n)(b+)

//Grammaire algébrique
//S->UV
//U->bUa+ba
//V->bV+b

//Grammaire homogène
//S->U.V
//U->U1+U2
//U1->B.U.A
//U2->B.A
//V->V1+V2
//V1->B.V
//V2->B

//Attribut
//S->U(a).V(b).(a=b)
//U(a)->U1(a)+U2(a)
//U1(a+1)->B.U(a).A
//U2(1)->B.A
//V(b)->V1(b)+V2(b)
//V1(b+1)->B.V(b)
//V2(1)->B

char *sMOT;
int bTp2AmorceR=kF;
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bT(int iDebut,int *piFin);

void Tp3AMORCER(){
	bTp2AmorceR=kV;
}

void Tp3INITIALISER(){
	Assert1("Tp2INITIALISER",bTp2AmorceR);
}

void Tp3TESTER(int iTest){
	int bEngendre,iFin,bSucces;
	Assert1("Tp2TESTER0",bTp2AmorceR);
	switch(iTest){
		case 1: sMOT="bbaab";break;
		case 2: sMOT="baaaaaaab";break;
		case 3: sMOT="bb";break;
		case 4: sMOT="";break;
		case 5: sMOT="bbbaaabbb";break;
		case 6: sMOT="bab";break;
		case 7: sMOT="bbaabbb";break;
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
//S->U(a).V(b).(a=b)


	int iX,iFin,aT,bT;
	int bSucces=bU(iDebut,&iX,&aT)&&bV(iX,&iFin,&bT)&&(aT==bT);
	*piFin=(bSucces)?iFin:iDebut;
	
	return (bSucces);

}
int bU(int iDebut,int *piFin,int *paN){
//U(a)->U1(a)+U2(a)
	int iFin=0,aT;
	int bSucces=bU1(iDebut,&iFin,&aT)||bU2(iDebut,&iFin,&aT);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=aT;
	return (bSucces);
}



int bU1(int iDebut,int *piFin,int *paN){
//U1(a+1)->B.U(a).A
	int iX,iY,iFin,aT;
	int bSucces=bB(iDebut,&iX)&&bU(iX,&iY,&aT)&&bA(iY,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=aT+1;
	return (bSucces);

}




int bU2(int iDebut,int *piFin,int *paN){
//U2(1)->B.A
	int iX,iFin;
	int bSucces=bB(iDebut,&iX)&&bA(iX,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=1;
	return (bSucces);

}


int bV(int iDebut,int *piFin,int *paN){
//V(b)->V1(b)+V2(b)
	int iFin,bT;
	int bSucces=bV1(iDebut,&iFin,&bT)||bV2(iDebut,&iFin,&bT);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=bT;
	return (bSucces);

}

int bV1(int iDebut,int *piFin,int *paN){
//V1(b+1)->B.V(b)
	int iX,iFin,bT;
	int bSucces=bB(iDebut,&iX)&&bV(iX,&iFin,&bT);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=bT+1;
	return (bSucces);

}
int bV2(int iDebut,int *piFin,int *paN){
//V2(1)->B
	int iFin;
	int bSucces=bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paN=1;
	return (bSucces);

}
