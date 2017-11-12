#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define N 100

void tri(int tab[],int size){
	int i=0,buf;
	while(i<size-1){
		if(tab[i]>tab[i+1]){
			buf=tab[i];
			tab[i]=tab[i+1];
			tab[i+1]=buf;
			i=0;
		}
		else{
			i++;
		}
	}
	
	
}


int
main( int nb_arg , char * tab_arg[] )
{
	
	char Nom_Prog[256] ;
	int nb_exec;
	int nb_proc;
	char nom_cmd[N];
	struct timeval start;
	struct timeval end;
	int time_use=0;
	int tube[2];
	int n,i,j,pid=0;
	int tab[N];
	if( nb_arg != 4 )
	{
		fprintf( stderr , "Usage : %s <nb execution> <command> <nb precessus>\n",
				tab_arg[0] );
		exit(-1);
	}
	sscanf( tab_arg[1] , "%i" , &nb_exec ) ;
	sscanf( tab_arg[3] , "%i" , &nb_proc ) ;
	strcpy( nom_cmd , tab_arg[2] );
	
	
	for (j=0; j<nb_proc; j++){
		pipe(tube);
		switch (fork()) {
			case -1:
				printf("error fork\n");
				exit(2);
			case 0:/*fils*/
				close(tube[0]);
				gettimeofday(&start,NULL);
				write(tube[1],&start,sizeof(struct timeval));
				for (i=0; i<nb_exec; i++){
					switch (fork()) {
						case -1:
							printf("error fork\n");
							exit(2);
						case 0:/*fils*/
							execlp(nom_cmd,nom_cmd,NULL);
							printf("error execlp\n");
							exit(2);
						default:/*pere*/
							wait(&n);
							if(n!=0){
								if(WIFEXITED(n))
									printf("Commande se termine anormalement: %i\n",WEXITSTATUS(n));
								if(WIFSIGNALED(n))
									printf("Execution termine par signal: %d\n",WTERMSIG(n));
								exit(2);
							}
							
					}
				}
				exit(0);
			default:/*pere*/
				pid=wait(&n);
				if(n!=0){
					printf("Execution pas reussie\n");
					exit(0);
				}
					
				gettimeofday(&end,NULL);
				close(tube[1]);
				read(tube[0],&start,sizeof(struct timeval));
				time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
				printf("time_use is %i\n",time_use);
				printf("pid=%i,n=%i\n",pid,n);
				tab[j]=time_use;
		}
		
	}
	
	printf("resultats:\n");
	for (i=0; i<nb_proc; i++) {
		tab[i]=tab[i]/nb_exec;
		printf("M%i=%i ",i,tab[i]);
	}
	printf("\n");
	
	tri(tab,nb_proc);
	printf("trier:\n");
	for (i=0; i<nb_proc; i++) {
		printf("M%i=%i ",i,tab[i]);
	}
	printf("\n");
	printf("temps moyenne :");
	if(nb_proc%2!=0)
		printf("%i\n",tab[nb_proc/2]);
	else
		printf("%i\n",(tab[nb_proc/2]+tab[nb_proc/2-1])/2);
}
