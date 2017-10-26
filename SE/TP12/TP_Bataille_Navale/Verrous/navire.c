#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

void plus_verrou( const int fd,	 bateau_t * bateau)  //mettre verrou sur la corp
{
    int i;
    coords_t * corps_bateau;
    corps_bateau = bateau_corps_get(bateau);
    struct flock verrou;
    verrou.l_type   = F_RDLCK ;		    	
    verrou.l_whence = 0 ;		
    verrou.l_len    = MER_TAILLE_CASE;	

    for(i=0; i<BATEAU_TAILLE; i++) 
    {
      verrou.l_start  = (long)corps_bateau->coords[i].pos;
      if(fcntl( fd , F_SETLK , &verrou )==-1){
		  printf("error\nerror\nerror\nerror\nerror\n") ;
		  //exit(1);
	  }
    }

}
void moins_verrou( const int fd,	 bateau_t * bateau)  //enleve du verrou sur la corp
{
    int i;
    coords_t * corps_bateau;
    corps_bateau = bateau_corps_get(bateau);
    struct flock verrou;

    verrou.l_type   = F_UNLCK ;		    	
    verrou.l_whence = 0 ;		
    verrou.l_len    = MER_TAILLE_CASE;	

    for(i=0; i<BATEAU_TAILLE; i++) 
    {
      verrou.l_start  = corps_bateau->coords[i].pos;
      fcntl( fd , F_SETLK , &verrou ) ;
 
    }

}


void plus_voisin( const int fd,bateau_t * bateau, coords_t * const liste_voisins)		//mettre verrou sur les voisin 
{
    int i;
    case_t case_mer ;
    int nb_voisins = coords_nb_get(liste_voisins) ;
    struct flock vecase;
    vecase.l_type   = F_RDLCK ;		
    vecase.l_whence = 0 ;	  	
    vecase.l_len    = MER_TAILLE_CASE;
    struct flock verrou;
    verrou.l_type   = F_WRLCK ;		
    verrou.l_whence = 0 ;	  	
    verrou.l_len    = MER_TAILLE_CASE;	
    for(i=0; i<nb_voisins; i++) 
    {
        vecase.l_start=liste_voisins->coords[i].pos;
		fcntl( fd , F_SETLKW , &vecase );
        mer_case_lire( fd , liste_voisins->coords[i], &case_mer );
        if( case_mer == MER_CASE_LIBRE )
        {
			vecase.l_type   = F_UNLCK ;
			fcntl( fd , F_SETLK , &vecase );
            verrou.l_start  = liste_voisins->coords[i].pos;
            fcntl( fd , F_SETLKW , &verrou );
        }
	else{
			vecase.l_type   = F_UNLCK ;
			fcntl( fd , F_SETLK , &vecase );
	}

    }

}



void moins_voisin( const int fd,bateau_t * bateau, coords_t * const liste_voisins){//enleve du verrou sur les voisin
   int i;

    struct flock verrou;
	int nb_voisins = coords_nb_get(liste_voisins) ; 
    verrou.l_type   = F_UNLCK ;		    	
    verrou.l_whence = 0 ;		
    verrou.l_len    = (long)MER_TAILLE_CASE;
    for(i=0; i<nb_voisins; i++) 
    {
        verrou.l_start  = (long)liste_voisins->coords[i].pos;
        fcntl( fd , F_SETLK , &verrou ) ; 
    }


}


void verrou_nb(const int fd){
	struct flock lock; 
	lock.l_type = F_WRLCK;
  	lock.l_start = MER_DEBUT_NB_BATEAUX;
  	lock.l_whence = SEEK_SET;
  	lock.l_len = MER_TAILLE_ENTETE;
 	fcntl(fd, F_SETLKW, &lock); 



}


void deverrou_nb(const int fd){
	struct flock lock; 
	lock.l_type = F_UNLCK;
  	lock.l_start = MER_DEBUT_NB_BATEAUX;
  	lock.l_whence = SEEK_SET;
  	lock.l_len = MER_TAILLE_ENTETE;
 	fcntl(fd, F_SETLK, &lock); 
}



/* 
 *  Programme principal 
 */
 
 
 
 
 
 
 
 
 
 

int
main( int nb_arg , char * tab_arg[] )
{
	case_t case_mer ;
  int seuil=10;
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;
  int fd_mer ;
  bateau_t * bateau = NULL ;
  int no_err = CORRECT ;
  coords_t * liste_voisins = NULL ;
  booleen_t ok = VRAI ;
  struct flock lock; 
    coord_t cible ;
  booleen_t acquisition ;
  int nb;
  booleen_t coule = FAUX ;
  int gagne=0;
  /*----------*/

  strcpy( nomprog , tab_arg[0] ) ;

  if( nb_arg != 4 )
    {
      fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n", 
	       nomprog );
      exit(-1);
    }

  if( strlen(tab_arg[2]) !=1 ) 
    {
      fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
	       nomprog , tab_arg[2] );
      exit(-1) ;
    }


  strcpy( fich_mer , tab_arg[1] );
  marque = tab_arg[2][0] ;
  sscanf( tab_arg[3] , "%f" , &energie );
  
  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );
/***********/  /***********/  /***********/  /***********/  /***********/  /***********/
/***********/  /***********/  /***********/  /***********/  /***********/  /***********/

  if( ( fd_mer = open( fich_mer , O_RDWR , 0644 )) == -1 )
    {
      fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_mer);
      exit(-1);
    }
    
  lock.l_type = F_WRLCK;
  lock.l_start = 0;
  lock.l_whence = SEEK_SET;
  lock.l_len = 0;
  fcntl(fd_mer, F_SETLKW, &lock);
       
  bateau = bateau_new( NULL , marque , 100) ;
  mer_bateau_initialiser( fd_mer,bateau );	
  lock.l_type = F_UNLCK;
  fcntl(fd_mer, F_SETLK, &lock);
  	verrou_nb(fd_mer);
  	mer_nb_bateaux_lire( fd_mer,&nb);

	if(nb==0)
		mer_nb_bateaux_ecrire( fd_mer,	1 );	
	else 
		mer_nb_bateaux_ecrire( fd_mer,	nb+1);
		
	deverrou_nb(fd_mer);
    while(nb<1)
		mer_nb_bateaux_lire( fd_mer,&nb);
    sleep(3);
    plus_verrou(fd_mer,bateau);  
    sleep(1);

/***********/  /***********/  /***********/  /***********/  /***********/  /***********/

/***********/  /***********/  /***********/  /***********/  /***********/  /***********/
  while(1){
	   /* 
       * deplacement des bateaux 
       */

   
		energie=energie-5; //consommation de l'energy pour chaque tour
		if(energie<0)
    	energie=0;
		printf("energie: %f\n",energie);

     
		 mer_bateau_est_touche( fd_mer,bateau ,&coule );//vérifier si la bateau a été touché
    
		 if(coule&&energie<seuil)
        {
            printf("Vous êtes mort\n");
            mer_bateau_couler( fd_mer,  bateau );
			verrou_nb(fd_mer);
			mer_nb_bateaux_lire( fd_mer,&nb);
            mer_nb_bateaux_ecrire( fd_mer , nb-1);
			deverrou_nb(fd_mer);
            close(fd_mer);
            exit(0);
        }
		mer_nb_bateaux_lire( fd_mer,&nb);//lire le nombre de bateau existe
		if(nb>1&&gagne==0)
			gagne=1;
		if(nb==1&&gagne==1){//quand il reste un seul bateau,il gagne
			printf("Vous avez gagné \n");
			mer_bateau_couler( fd_mer,  bateau );
			verrou_nb(fd_mer);
			mer_nb_bateaux_ecrire( fd_mer , 0);
			deverrou_nb(fd_mer);
			close(fd_mer);
			exit(0);
		}
	//déplacement de la bateau
		  if( (no_err = mer_voisins_rechercher( fd_mer,
							bateau,
							&liste_voisins )) )
		{
		  fprintf( stderr, "%s : erreur %d dans mer_voisins_rechercher\n",
			   nomprog , no_err );
		  exit(no_err) ;
		}

		  plus_voisin( fd_mer, bateau,liste_voisins);//verrou sur les voisin
		  moins_verrou(fd_mer,bateau);//enleve de verrou sur la corps
		  printf( "Liste des voisins :\n");
		  coords_printf( liste_voisins );
		  printf("\n\n");
		  if( (no_err = mer_bateau_deplacer( fd_mer,
						 bateau,
						 liste_voisins,
						 &ok )) )
		  {
			 fprintf( stderr, "%s : erreur %d dans mer_bateau_deplacer\n",
			   nomprog , no_err );
			 exit(no_err) ;
		  }
		  moins_voisin( fd_mer, bateau,liste_voisins); //enleve les verrou sur voisin
		  if(energie>=seuil){   //pose de verrou sur le corp de la bateau
			plus_verrou(fd_mer,bateau);
			printf("bouclier\n");
		  }
		  coords_destroy(&liste_voisins);
		  if( ok )
		{
		  printf( "Deplacement reussi\n");
		}
		  else
		{
		  printf(" Deplacement impossible\n");
		}


		if(nb>1){//quand il y a plus de 1 bateau, le bateau tirer
			
			if( (no_err = mer_bateau_cible_acquerir( fd_mer,
								   bateau,
								   &acquisition,
								   &cible )) )
				{
				  fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_acquerir\n",
					   nomprog , no_err );
				  exit(no_err) ;
				}

			  if( acquisition )
				{
				  printf("Acquisition d'une cible par le bateau \n");
				  bateau_printf( bateau );
				  printf( "\n-->La cible choisie est la case ");
				  coord_printf( cible );
				  printf( "\n\n");
					  //pose de verrou sur le cible
					lock.l_type = F_WRLCK;
					lock.l_start = cible.pos;
					lock.l_whence = 0;
					lock.l_len = MER_TAILLE_CASE;
					if(fcntl(fd_mer, F_SETLK, &lock)!=-1){//possible de tirer
						mer_case_lire( fd_mer, cible, &case_mer );
						if(case_mer!=MER_CASE_LIBRE){
							if( (no_err = mer_bateau_cible_tirer( fd_mer,
											cible)) )
							{
							  fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer\n",
								   nomprog , no_err );
							  exit(no_err) ;
							}
							
						}
							//enleve de verrou
							lock.l_type = F_UNLCK;
							fcntl(fd_mer, F_SETLK, &lock);

						
						
					}
					else{
						printf("--->impossible de tirer\n");
					}
				}
			  else
				{
				  printf("Pas d'acquisition de cible pour le bateau \n");
				  bateau_printf( bateau );
				  printf( "\n");
				}
			





	
	}
	


 
  	sleep(rand()%4+1);
  }
/***********/  /***********/  /***********/  /***********/  /***********/  /***********/ 
  

  

  /***********/  /***********/  /***********/  /***********/  /***********/  /***********/
  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );

  exit(0);
}
