#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

void plus_verrou( const int fd,	 bateau_t * bateau)  
{
    int i;
    coord_t * corps_bateau;
    corps_bateau = bateau_corps_get(bateau);
    struct flock verrou;

  

    verrou.l_type   = F_WRLCK ;		    	
    verrou.l_whence = 0 ;		
    verrou.l_len    = MER_TAILLE_CASE;	
  //  verrou.l_pid    = bateau_pid_lire(*bateau);	
    for(i=0; i<BATEAU_TAILLE; i++) 
    {
      verrou.l_start  = (long)corps_bateau[i].pos;
      fcntl( fd , F_SETLKW , &verrou ) ;
 
    }

}
void moins_verrou( const int fd,	 bateau_t * bateau)  
{
    int i;
    coord_t * corps_bateau;
    corps_bateau = bateau_corps_get(bateau);
    struct flock verrou;

  

    verrou.l_type   = F_UNLCK ;		    	
    verrou.l_whence = 0 ;		
    verrou.l_len    = MER_TAILLE_CASE;	
    //verrou.l_pid    = bateau_pid_lire(*bateau);	
    for(i=0; i<BATEAU_TAILLE; i++) 
    {
      verrou.l_start  = (long)corps_bateau[i].pos;
      fcntl( fd , F_SETLK , &verrou ) ;
 
    }

}







/* 
 *  Programme principal 
 */
 
 
 
 
 
 
 
 
 
 

int
main( int nb_arg , char * tab_arg[] )
{
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
  
  
  	mer_nb_bateaux_lire( fd_mer,&nb);
	if(nb==0)
		mer_nb_bateaux_ecrire( fd_mer,	1 );	
	else 
		mer_nb_bateaux_ecrire( fd_mer,	nb+1);	
		
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_type = F_UNLCK;
    fcntl(fd_mer, F_SETLK, &lock);
    plus_verrou(fd_mer,bateau);  
/***********/  /***********/  /***********/  /***********/  /***********/  /***********/

/***********/  /***********/  /***********/  /***********/  /***********/  /***********/
  while(1){
	   /* 
       * deplacement des bateaux 
       */
   //verrou sur touts le fichier
	/*lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    fcntl(fd_mer, F_SETLKW, &lock);*/
   
    energie=energie-5; //consommation de l'energy pour chaque tour
    

    
    mer_bateau_est_touche( fd_mer,bateau ,&coule );//vérifier si la bateau a été touché
     if(coule) 
        {
            printf("Vous êtes mort\n");
            mer_bateau_couler( fd_mer,  bateau );  
            mer_nb_bateaux_ecrire( fd_mer , nb-1);
            close(fd_mer);
            exit(0);
        }
    
    
    
    
    
	mer_nb_bateaux_lire( fd_mer,&nb);//lire le nombre de bateau existe
      if( (no_err = mer_voisins_rechercher( fd_mer,
					    bateau,
					    &liste_voisins )) )
	{
	  fprintf( stderr, "%s : erreur %d dans mer_voisins_rechercher\n",
		   nomprog , no_err );
	  exit(no_err) ;
	}

      printf( "Liste des voisins :\n");
      coords_printf( liste_voisins );
      printf("\n\n");
      
      
      	
    moins_verrou(fd_mer,bateau);  //enleve le verrou de sa position enciente
      
	//déplacement de la bateau
      if( (no_err = mer_bateau_deplacer( fd_mer,
					 bateau,
					 liste_voisins,
					 &ok )) )
	{
	  fprintf( stderr, "%s : erreur %d dans mer_bateau_deplacer\n",
		   nomprog , no_err );
	  exit(no_err) ;
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
	
	if(1){   //fait verrou pour le nouveau position
    	plus_verrou(fd_mer,bateau);  
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
			}
		  else
			{
			  printf("Pas d'acquisition de cible pour le bateau \n");
			  bateau_printf( bateau );
			  printf( "\n");
			}

		  if( (no_err = mer_bateau_cible_tirer( fd_mer,
							cible)) )
			{
			  fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer\n",
				   nomprog , no_err );
			  exit(no_err) ;
			}
	
	}
	
	//déverrou
	/*lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_type = F_UNLCK;
    fcntl(fd_mer, F_SETLK, &lock);*/

 
  	sleep(1);
  }
/***********/  /***********/  /***********/  /***********/  /***********/  /***********/ 
  

  







  /***********/
  /* A FAIRE */
  /***********/
  /***********/  /***********/  /***********/  /***********/  /***********/  /***********/
  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );

  exit(0);
}
