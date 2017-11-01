/* 
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include <mer.h>
#include <bateaux.h>


#define SIG_JEU SIGUSR1
#define N 100
int nb_bateau=0;
bateaux_t * bt = (bateaux_t *) NULL ;

char marque='A';
int fd_mer ;

void hdl_jouer(int sig,siginfo_t *siginfo){
	pid_t pid=siginfo->si_pid;
	int num_bt;
	bateau_t * bateau = NULL ;
	coords_t * liste_voisins = NULL ;
	booleen_t ok = VRAI ;
	coord_t cible ;
	booleen_t acquisition ;
	int tirer_possible=0;
	case_t case_mer ;
	
	num_bt=bateaux_pid_seek(bt,pid);
	if(num_bt!=-1){//deplacer et tirer
		printf("deplacement d'un bateau: %i\n",num_bt);
		bateau=bateaux_bateau_get(bt,num_bt);
		mer_voisins_rechercher( fd_mer,bateau,&liste_voisins );
		mer_bateau_deplacer( fd_mer,bateau,liste_voisins,&ok );
		coords_destroy(&liste_voisins);
		//tirer d'un bateau
		if(bateaux_nb_get(bt)>1){
			printf("Tirer d'un bateau : %i\n",num_bt);
			mer_bateau_cible_acquerir( fd_mer, bateau,&acquisition,&cible );
			if( acquisition ){
				printf( "\n-->La cible choisie est la case ");
				if(tirer_possible){//possible de tirer
					mer_case_lire( fd_mer, cible, &case_mer );
					if(case_mer!=MER_CASE_LIBRE)
						mer_bateau_cible_tirer( fd_mer,cible);
				}
				else
					printf("Impossible de tirer\n");
			}
		}
	}
	else{//initialiser un nouveau bateau
		printf("Initiation d'un bateau\n");

		bateau = bateau_new( NULL , marque , pid) ;
		mer_bateau_initialiser( fd_mer,bateau );
		bateaux_bateau_add( bt ,bateau ) ;
		mer_voisins_rechercher( fd_mer,bateau,&liste_voisins );
		sleep(1);
		mer_bateau_deplacer( fd_mer,bateau,liste_voisins,&ok );
		nb_bateau++;
		marque++;
		bateau_destroy(&bateau);
		kill(pid,SIG_JEU);//renvoie un signal informe que le bateau est initialise
	}
	
	
	
	
	signal(SIG_JEU,hdl_jouer);
}




/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256] ;

/*
 * FONCTIONS LOCALES
 */


/*
 * Programme Principal
 */
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
	 struct sigaction act_jouer;
     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer> \n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );
     
     /*
      * Affichage pid bateau amiral 
      */
     
     printf(" PID bateau amiral = %d\n" , getpid() ) ;

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());
 //commencer
	act_jouer.sa_sigaction=hdl_jouer;
	sigaction(SIG_JEU,&act_jouer,NULL);
	
	bt=bateaux_new();
	fd_mer = open( fich_mer , O_RDWR , 0644 );
	//boucle d'attente
	while (1) {
		pause();
	}
     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}

