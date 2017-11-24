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
int extrait=0;
void hdl_extrait(){//fonction quand recu un signal qui informe que le recepeteur a extrait le message
	struct sigaction act;
	act.sa_sigaction=hdl_extrait;
	sigaction(SIGUSR2,&act,NULL);
	extrait=1;//cette valeur indique que le message est extrait,donc commancer a ecrit les nouveaux messages
	
}

void hld_fin(){//fonction quand le nombre de envoyer est suffit
	printf("Fin de envoyer\n");
	exit(0);
}


int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
	 int fd,i;
	char message[MESSAGES_TAILLE] ;
	struct sigaction act;
	struct sigaction act2;
	int pid;
     /*-----*/

     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 2 )
       {
	 fprintf( stdout , "%s - Emetteur dans la communication par fichier\n\n" , nomprog ) ;
	 fprintf( stdout , "Usage : %s <pid> \n" , nomprog ) ;
	 exit(1) ; 
       }
	sscanf( tab_arg[1] , "%i" , &pid ) ;

	act2.sa_sigaction=hld_fin;
	act.sa_sigaction=hdl_extrait;
	sigaction(SIGUSR2,&act,NULL);
	sigaction(SIGUSR1,&act2,NULL);
	fd=open(FILE_NAME,O_RDWR|O_CREAT , 0644);
	file_remplir( message , 'X') ;
	printf("Commencer à envoyer les messages\n");
	while(1){//boucle de envoyer de message
		lseek(fd, 0, SEEK_SET);
		write(fd,message,MESSAGES_TAILLE);
		kill(pid,SIGUSR2);//informer le recepteur que le message a ete ecrit	
		while(extrait==0);//attente que le message ecrit est extrait par le recepteur
		extrait=0;
	}

    
     exit(0);
}
