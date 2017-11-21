#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <msg_messages.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
     message_t message ; 
     int lg=sizeof(corps_t);
     int cle,i;
     struct timeval temps ; 
     double temps_fin;
     double temps_debut;
     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Recepteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );
     cle=msgget(1,IPC_CREAT|0666);
     
     for(i=0;i<MESSAGES_NB;i++){	     
	    msgrcv(cle,&message,lg,MSG_TYPE_RECEPTEUR,0);     
     }
      gettimeofday(&temps, NULL);  
      temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);
      temps_debut=message.corps.temps_debut;
      printf("\nTemps de reception des massages %s =  %.6lf secondes  !!!\n", nomprog , temps_fin - temps_debut);  


     
     exit(0);
}
