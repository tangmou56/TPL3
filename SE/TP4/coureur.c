#include <messages.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#define N 100

int cle,cleex;


void hdl_ab(int sig){
	requete_t req;
	reponse_t rep;
	int lgq=sizeof(corps_requete_t);
	int lgp=sizeof(corps_reponse_t);
	req.corps.dossard=getpid();
	req.corps.etat=ABANDON;
	msgsnd(cle,&req,lgq,0);	
	msgrcv(cle,&rep,lgp,getpid(),0);
	messages_afficher_erreur( rep.corps.compte_rendu )  ;
	exit(0);
}





int main(int nb_arg , char * tab_arg[]){
	requete_t req;
	reponse_t rep;
	int lgq=sizeof(corps_requete_t);	
	int lgp=sizeof(corps_reponse_t);
	
	req.type=PC_COURSE;
	req.corps.dossard=getpid();
	req.corps.etat=EN_COURSE;
	struct sigaction act;
	if( nb_arg != 2 )
	{
		fprintf( stderr , "Usage : %s <cle>\n",tab_arg[0] );
		exit(-1);
	}
	sscanf( tab_arg[1] , "%i" , &cleex ) ;
	cle=msgget(cleex,IPC_CREAT|0666);
	act.sa_sigaction=hdl_ab;
	sigaction(SIGINT,&act,NULL);
	messages_initialiser_attente() ;
	while(1){
		msgsnd(cle,&req,lgq,0);	
		msgrcv(cle,&rep,lgp,getpid(),0);
				
		messages_afficher_reponse( &rep );
		if(rep.corps.etat==ARRIVE|| rep.corps.etat==DECANILLE)
			exit(0);

		messages_attendre_tour() ;
	}
}