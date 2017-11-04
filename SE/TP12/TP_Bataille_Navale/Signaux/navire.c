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
#define SIG_COULE SIGTRAP
#define SIG_BOUCLIER SIGUSR2
#define SIG_GAGNER SIGABRT
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
void hdl_coule(int sig,siginfo_t *siginfo){
	printf("Vous etes mort\n");
	exit(0);
	
	
}
void hdl_gagner(int sig,siginfo_t *siginfo){
	printf("Vous avez gagne\n");
	exit(0);
	
	
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
	int energie=40;
    struct sigaction act_jouer;
	struct sigaction act_coule;
	struct sigaction act_gagner;
	int bouc=1;
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
	act_coule.sa_sigaction=hdl_coule;
	sigaction(SIG_COULE,&act_coule,NULL);
	act_gagner.sa_sigaction=hdl_gagner;
	sigaction(SIG_GAGNER,&act_gagner,NULL);
	kill(pid_amiral,SIG_JEU);

	while (1) {
		sleep(2);
		kill(pid_amiral,SIG_JEU);
		sleep(1);
		energie=energie-5;
		if(energie<0)
			energie=0;
		if(energie<=10){
			printf("enleve du bouclier\n");
			kill(pid_amiral,SIG_BOUCLIER);
			bouc=0;
		}
		printf("energie: %i\n",energie);
	}

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}

