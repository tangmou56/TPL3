#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>

/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;
 	 int fd_mer ;
 	 int no_err = CORRECT ;
 	 time_t time_pre=0;
 	 struct stat buf;
	 struct flock lock; 	  
     /*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );


     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );
  /***********/  /***********/  /***********/  /***********/  /***********/  /***********/

 /***********/  /***********/  /***********/  /***********/  /***********/  /***********/
  /* 
   * dernière motif de fichier mer
   */
	  stat(fich_mer,&buf);
	  printf("date: %ld\n",buf.st_mtime);
 /***********/  /***********/  /***********/  /***********/  /***********/  /***********/





 /***********/  /***********/  /***********/  /***********/  /***********/  /***********/
	while(1){
		stat(fich_mer,&buf);
		if(time_pre==buf.st_mtime){
			
		}
		else{



			/* 
			* Ouverture fichier mer
			*/

			if( ( fd_mer = open( fich_mer , O_RDWR , 0644 )) == -1 )
			{
				fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_mer);
				exit(-1);
			}
			

   			lock.l_type = F_RDLCK;
    		lock.l_start = 0;
    		lock.l_whence = SEEK_SET;
   		 	lock.l_len = 0;
    		fcntl(fd_mer, F_SETLKW, &lock);


			printf(" Mer initiale: \n");

			if( (no_err = mer_afficher(fd_mer) )) 
			{
				fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
				nomprog , no_err );
				exit(no_err) ;
			}
			lock.l_start = 0;
    		lock.l_whence = SEEK_SET;
   		 	lock.l_len = 0;
	 		lock.l_type = F_UNLCK;
		    fcntl(fd_mer, F_SETLKW, &lock);
		    close(fd_mer);
		    

		}
		time_pre=buf.st_mtime;
		
		
		sleep(1);
	}

  /***********/  /***********/  /***********/  /***********/  /***********/  /***********/



  /***********/  /***********/  /***********/  /***********/  /***********/  /***********/
     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
