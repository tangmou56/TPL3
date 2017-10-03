#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

/* 
 *  Programme principal 
 */

int
main( int nb_arg , char * tab_arg[] )
{
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
    
  lock.l_type = F_RDLCK;
  lock.l_start = 0;
  lock.l_whence = SEEK_SET;
  lock.l_len = 0;
  fcntl(fd_mer, F_SETLKW, &lock);
       
  bateau = bateau_new( NULL , marque , 100) ;
  mer_bateau_initialiser( fd_mer,bateau );	
  
  lock.l_type = F_UNLCK;
  fcntl(fd_mer, F_SETLKW, &lock);
/***********/  /***********/  /***********/  /***********/  /***********/  /***********/

/***********/  /***********/  /***********/  /***********/  /***********/  /***********/
  while(1){
	   /* 
       * deplacement des bateaux 
       */

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
