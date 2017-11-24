#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <file_messages.h>

#define BIG_TAILLE MESSAGES_NB*MESSAGES_TAILLE
char big_buffer[BIG_TAILLE] ;
int pid_emetteur;
int ecrit=0;
int n=1;
void hdl_ecrit(int sig,siginfo_t *siginfo){//handler quand recu le signal qui informe que les nouveaux messages sont ecrit
	if(n){//premier fois recu le signal,garde le pid du emetteur
		pid_emetteur=siginfo->si_pid;
		n=0;
	}
	struct sigaction act;
	act.sa_sigaction=hdl_ecrit;

	sigaction(SIGUSR2,&act,NULL);
	ecrit=1;//cette valeur indique que un nouveau message est ecrit
}


void effacer(int fd){//effacer le fichier
	ftruncate(fd,0);
}


int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
     int fd,i=0;
	char message[MESSAGES_TAILLE] ;
	struct sigaction act;
	int pid,res;
	int bytes = 0;
	struct timeval temps ;
	double temps_debut;
	double temps_fin;
     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
       {
	 fprintf( stdout , "%s - Recepteur dans la communication par fichier\n\n" , nomprog ) ;
	 fprintf( stderr , "Usage : %s \n" , nomprog ) ;
	 exit(1) ; 
       }
	pid=getpid();
	printf("PID=%i\n",pid);
	fd=open(FILE_NAME,O_RDWR|O_CREAT , 0644);//ouverture du fichier
	act.sa_sigaction=hdl_ecrit;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGUSR2,&act,NULL); //initiation de traitement de signal
	pause();//attente que emetteur commancer a envoyer les messages
	gettimeofday(&temps, NULL);//temps de 1er message envoie
	temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);
	for(i=0;i<MESSAGES_NB;i++){//boucle de reception des message
		lseek(fd, 0, SEEK_SET);
		res=read(fd,message,MESSAGES_TAILLE);
		bytes += res;
		effacer(fd);
		kill(pid_emetteur,SIGUSR2);//informer le emetteur que le message est extrait		
		while(ecrit==0);//attente que nouveau message est ecrit
		ecrit=0;
		if(i%5000==0)
			printf("%i\n",i);
	}
	gettimeofday(&temps, NULL);//temps de dernier message envoie
	temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);
	kill(pid_emetteur,SIGUSR1);//envoyer un signal a emtteur pour terminer son processus
    printf("Process %d finished, %d bytes read\n", getpid(), bytes);
    printf("\nTemps de transfert des messages %s =  %.6lf secondes  !!!\n", nomprog , temps_fin - temps_debut);//affichage de resultat
     exit(0);
}
