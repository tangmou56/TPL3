/* 
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>
#define SIG_JEU SIGUSR1
/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

int Energie ; 

/*
 * Handlers 
 */
void hdl_jouer(int sig,siginfo_t *siginfo){
	signal(SIG_JEU,hdl_jouer);


}




/*
 * Programme Principal 
 */

int
main( int nb_arg , char * tab_arg[] )
{
	int i;
  char nomprog[128] ;
  pid_t pid_amiral ;
  pid_t pid_bateau = getpid()  ;
  struct sigaction act_jouer;
  /*----------*/

  /* 
   * Capture des parametres 
   */

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <pid amiral>\n", 
	       tab_arg[0] );
      exit(-1);
    }

  /* Nom du programme */
  strcpy( nomprog , tab_arg[0] );
  sscanf( tab_arg[1] , "%d" , &pid_amiral ) ; 

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);


  /* Affectation du niveau d'energie */
  Energie = random()%BATEAU_MAX_ENERGIE ;
  
  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );

  /*
   * Deroulement du jeu 
   */
	act_jouer.sa_sigaction=hdl_jouer;
	sigaction(SIG_JEU,&act_jouer,NULL);
	
	kill(pid_amiral,SIG_JEU);
	
	while (1) {
		sleep(2);
		kill(pid_amiral,SIG_JEU);
	}

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}

