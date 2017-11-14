#include <messages.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100


void main(){
	requete_t req;
	reponse_t rep;
	int lg=sizeof(corps_requete_t);
	int cle=msgget(PC_COURSE,IPC_CREATE|0666);
	coureur_t tab[N];
	int nb_cr=0,i,trouve=0;
	while(1){
		msgrcv(cle,&req,&lg,PC_COURSE,0);
		for(i=0,i<nb_cr,i++){
			if(tab[i].dossard==req.corps.dossard)
				trouve=1;		
		}
		if(trouve){
			tab[i].distance=tab[i].distance+10;
			rep.type=req.corps.dossard;
			rep.corps.nb_coureurs=nb_cr;
			msgsnd(cle,&rep,sizeof(corps_reponse_t),0);
		}
		else{
			tab[nb_cr].distance=0;
			tab[nb_cr].dossard=req.corps.dossard;
			nb_cr++;
					
		}
		trouve=0;
	}
}