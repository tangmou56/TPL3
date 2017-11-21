#include <stdio.h>
#include <unistd.h>	/* close, read, write */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/*open */
#include <sys/stat.h>
#include <fcntl.h>
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
     int res,i=0;  
     int open_mode = O_RDONLY;  
     int bytes = 0; 
     message_t msg;
     msg.fini=0;
     struct timeval temps ;
     double temps_debut;
     double temps_fin;
     /*-----*/
     strcpy( nomprog , tab_arg[0] ); 
     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Recepteur dans la communication par flot\n\n" , tab_arg[0] );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }

      printf("Consumer Program beginning...\n");  
 
      if(access(FIFO_NAME, F_OK) == -1){  
        res = mkfifo(FIFO_NAME, 0777);  
        if(res != 0){  
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);  
            exit(EXIT_FAILURE);  
        }  
      }  
      printf("Process %d opeining FIFO O_RDONLY\n", getpid());  
      pipe_fd = open(FIFO_NAME, open_mode);  
      printf("Process %d result %d\n", getpid(), pipe_fd);  
  
      printf("Attente les messages\n");
      if (pipe_fd != -1)  
      {  
          do{  
              res = read(pipe_fd,&msg,sizeof(message_t));  
              bytes += res;  
          }while(res > 0&&msg.fini==0);  
          
      }  
      else  
      {  
          exit(EXIT_FAILURE);  
      }  
      gettimeofday(&temps, NULL);
      temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);
      read(pipe_fd,&temps_debut,sizeof(double)); 
      close(pipe_fd); 

      printf("Process %d finished, %d bytes read\n", getpid(), bytes);  
      printf("\nTemps d'execution du programme %s =  %.6lf secondes  !!!\n", nomprog , temps_fin - temps_debut);  
      unlink(FIFO_NAME);
      exit( 0 );
}
