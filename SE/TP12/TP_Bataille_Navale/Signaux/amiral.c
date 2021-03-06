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

#define SIG_GAGNER SIGABRT
#define SIG_JEU SIGUSR2
#define SIG_COULE SIGRTMIN+12
#define SIG_BOUCLIER SIGRTMIN+11
#define N 100
int nb_bateau=0;//indice sur la derniere element dans la liste bouclier
int nb_bateau2=0;//quand nb_bateau2>1,ça veut dir que le jeu est commencé, prochaine fois quand le nb de bateau est 1,le jeu fini
bateaux_t * bt = (bateaux_t *) NULL ;//liste de bateau
char marque='A';
int fd_mer ;
int bouclier[N];//1=bouclier active,0=pas active
int commencer=0;

void hdl_bouclier(int sig,siginfo_t *siginfo,void *context){//Changer les situations des boucliers
	pid_t pid=siginfo->si_pid;
	int num_bt;
	struct sigaction act_bouclier;
	act_bouclier.sa_sigaction=hdl_bouclier;
	act_bouclier.sa_flags=SA_SIGINFO;
	printf("signal SIG_BOUCLIER reçu pid:%d\n",pid);
	num_bt=bateaux_pid_seek(bt,pid);
	if(num_bt!=-1){
		bouclier[num_bt]=0;
		printf("##################\nbateau %i enleve du bouclier,pid=%d\n#################\n",num_bt,pid);

	}
	sigaction(SIG_BOUCLIER,&act_bouclier,NULL);
}

void hdl_jouer(int sig,siginfo_t *siginfo,void *context){//fonction principale pour le jeu. deplacement,tirer,et couler
	pid_t pid=siginfo->si_pid;
	pid_t pid_cible;
	int num_bt,num_cible;
	bateau_t * bateau = NULL ;
	bateau_t * bateau_cible = NULL ;
	coords_t * liste_voisins = NULL ;
	booleen_t ok = VRAI ;
	coord_t cible ;
	booleen_t acquisition ;
	int tirer_possible=0;
	int no_err = CORRECT ;
	case_t case_mer ;
	printf("signal SIG_JEU reçu pid:%d\n",pid);	
	struct sigaction act_jouer;
	act_jouer.sa_sigaction=hdl_jouer;
	act_jouer.sa_flags=SA_SIGINFO;

	num_bt=bateaux_pid_seek(bt,pid);
	if(nb_bateau2==1&&commencer==1&&num_bt!=-1){//Quand il reste un bateau,le jeu fini
		printf("Jeu fini\n");
		bateau=bateaux_bateau_get(bt,num_bt);
		printf("bateau %c a gagné\n",bateau_marque_get(bateau));
		kill(pid,SIG_GAGNER);
		mer_bateau_couler(fd_mer,bateau);
		exit(0);
	}
	
	
	if(num_bt!=-1){//deplacer et tirer
		printf("deplacement d'un bateau: %i,pid=%d\n",num_bt,pid);
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
				coord_printf( cible );
				mer_case_lire( fd_mer, cible, &case_mer );
				num_cible=bateaux_marque_seek( bt,case_mer ) ;
				if(num_cible!=-1){
					bateau_cible=bateaux_bateau_get(bt,num_cible);
					pid_cible=bateau_pid_get(bateau_cible);
					if(bouclier[num_cible]==0)
						tirer_possible=1;
					if(tirer_possible){//possible de tirer
						
						if(case_mer!=MER_CASE_LIBRE){
							kill(pid_cible,SIG_COULE);
							mer_bateau_cible_tirer( fd_mer,cible);
							mer_bateau_couler(fd_mer,bateau_cible);
							nb_bateau2--;
						}
					}
					else
						printf("Impossible de tirer\n");
					
				}
			}
		}
	}
	else if(pid!=0){//initialiser un nouveau bateau
		printf("Initiation d'un bateau\n");
		bateau = bateau_new( NULL , marque , pid) ;
		no_err=mer_bateau_initialiser( fd_mer,bateau );
		if( no_err == ERREUR ){
	      		printf( "mer_bateau_initialiser n'a pas pu placer le bateau pid:%d \n",pid );
	    	}
		else{
			bateaux_bateau_add( bt ,bateau ) ;
			bouclier[nb_bateau]=1;
			nb_bateau++;
			nb_bateau2++;
			marque++;
			bateau_destroy(&bateau);
			kill(pid,SIG_JEU);
		}
		
	}
	
	sigaction(SIG_JEU,&act_jouer,NULL);
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
	 struct sigaction act_bouclier;

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
	act_bouclier.sa_sigaction=hdl_bouclier;
	act_bouclier.sa_flags=SA_SIGINFO;

	sigaction(SIG_BOUCLIER,&act_bouclier,NULL);
	act_jouer.sa_sigaction=hdl_jouer;
	act_jouer.sa_flags=SA_SIGINFO;

	
	sigaction(SIG_JEU,&act_jouer,NULL);

	bt=bateaux_new();
	fd_mer = open( fich_mer , O_RDWR , 0644 );

	//boucle d'attente
	while (1) {
		pause();
		if(nb_bateau2>1)
			commencer=1;

	}
     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}

