#ifndef _MSG_MESSAGES_H_
#define _MSG_MESSAGES_H_

#include <messages.h>


#define FIFO_NAME "./my_fifo"


typedef struct message
{
  int fini;
  char message[MESSAGES_TAILLE] ; 
} message_t ;


/*
 * Definition des fonctions 
 */

/* Affichage d'un message */
extern
void pipe_afficher( char * const message );

/* Remplissage d'un message */
extern
void pipe_remplir( char * message , const char val ) ;

#endif
