#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <msg_messages.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
     message_t message ; 
     struct timeval temps ; 
     int lg=sizeof(corps_t);
     int cle;
     int i;
     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Emetteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );

     cle=msgget(1,IPC_CREAT|0666);
     gettimeofday(&temps, NULL);  //temps de envoyer de la 1er message,ecrit dans la structure de message,et envoye ensemble avec le message
     message.corps.temps_debut=temps.tv_sec+(temps.tv_usec/1000000.0);
     msg_remplir( &message , 'X');

     for(i=0;i<MESSAGES_NB;i++){//boucle de envoyer des messages
     	msgsnd(cle,&message,lg,0);	
     }
     printf("Fin d'envoyer\n");


     exit(0);
}
