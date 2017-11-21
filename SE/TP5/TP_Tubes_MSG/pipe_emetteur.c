#include <stdio.h>
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* mknod */
#include <sys/types.h>	/* open */
#include <fcntl.h>
#include <unistd.h>	/* close , write */
#include <sys/time.h>
#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif
#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;
     int pipe_fd; 
     int res,i; 
     message_t msg;
     struct timeval temps ;
     double temps_debut;
     /*----------*/

     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }
	

     printf("Process %d opening FIFO \n",getpid());  
      
     pipe_fd = open(FIFO_NAME, O_RDWR , 0644);  
     printf("Process %d result %d\n", getpid(), pipe_fd);  
    
     printf("Commencer à envoyer les message\n");
     pipe_remplir( msg.message , 'X') ;
     msg.fini=0;
     gettimeofday(&temps, NULL);
     temps_debut=temps.tv_sec+(temps.tv_usec/1000000.0);
     for(i=0;i<MESSAGES_NB-1;i++){
	write(pipe_fd,&msg,sizeof(message_t));
     }
     msg.fini=1;
     write(pipe_fd, &msg,sizeof(message_t));
     write(pipe_fd, &temps_debut,sizeof(double));
     printf("Fin d'exécution\n");

}
 
