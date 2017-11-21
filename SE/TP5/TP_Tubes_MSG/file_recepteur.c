#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <file_messages.h>

#define BIG_TAILLE MESSAGES_NB*MESSAGES_TAILLE
char big_buffer[BIG_TAILLE] ;
int pid_emetteur;
int ecrit=0;
int n=1;
void hdl_ecrit(int sig,siginfo_t *siginfo){
	if(n){
		pid_emetteur=siginfo->si_pid;
		n=0;
	}
	struct sigaction act;
	act.sa_sigaction=hdl_ecrit;
	act.sa_flags=0;
	sigaction(SIGUSR2,&act,NULL);
	ecrit=1;
}


void effacer(int fd){
	ftruncate(fd,0);
}


int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
     int fd,i=0;
	 struct flock lock;
	char message[MESSAGES_TAILLE] ;
	struct sigaction act;
	lock.l_start = 0;
	lock.l_whence = SEEK_SET;
	lock.l_len = 0;
	int pid,res;
	int bytes = 0;
	struct timeval temps ;
	double temps_debut;
	double temps_fin;
     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
       {
	 fprintf( stdout , "%s - Recepteur dans la communication par fichier\n\n" , nomprog ) ;
	 fprintf( stderr , "Usage : %s \n" , nomprog ) ;
	 exit(1) ; 
       }
	pid=getpid();
	printf("PID=%i\n",pid);
	fd=open(FILE_NAME,O_RDWR|O_CREAT , 0644);
	act.sa_sigaction=hdl_ecrit;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGUSR2,&act,NULL);
	pause();
	gettimeofday(&temps, NULL);
	temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);
	for(i=0;i<MESSAGES_NB;i++){
		lock.l_type = F_RDLCK;
		fcntl(fd, F_SETLKW, &lock);
		lseek(fd, 0, SEEK_SET);
		res=read(fd,message,MESSAGES_TAILLE);
		bytes += res;

		effacer(fd);
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		kill(pid_emetteur,SIGUSR2);
		while(ecrit==0)
			kill(pid_emetteur,SIGUSR2);
		ecrit=0;
		if(i%10000==0)
			printf("%i\n",i);
	}
	gettimeofday(&temps, NULL);
	temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);
	kill(pid_emetteur,SIGUSR1);
    printf("Process %d finished, %d bytes read\n", getpid(), bytes);
    printf("\nTemps de transfert des messages %s =  %.6lf secondes  !!!\n", nomprog , temps_fin - temps_debut);
     exit(0);
}
