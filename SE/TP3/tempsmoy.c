#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define N 100



void sortir(int tab[],int * size,int indice){//sortir d'un element de une liste,et moins 1 la taille
	int i,mid;
	for(i=indice;i<*size-1;i++){
		tab[i]=tab[i+1];
	}
	*size=*size-1;
	if(*size<0)
		*size=0;

}



void tri(int tab[],int *size){//trier d'une liste croissante,quand un element est 0,le sortie de la liste
	int i=0,buf;
	while(i<*size-1){
		if(tab[i]==0)
			sortir(tab,size,i);
		else if(tab[i]>tab[i+1]){
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
	int fd;
	char Nom_Prog[256] ;
	int nb_exec;//nombre de execution
	int nb_proc;//nombre de processus
	char nom_cmd[N];//nom de la commande
	struct timeval start;
	struct timeval end;
	int time_use=0;
	int tube[2];
	int n,i,j,pid=0;
	int tab[N];//table de resultat
	int tab_pid[N];//table de pid des fils
	if( nb_arg != 4 )
	{
		fprintf( stderr , "Usage : %s <nb execution> <command> <nb precessus>\n",
				tab_arg[0] );
		exit(-1);
	}
	sscanf( tab_arg[1] , "%i" , &nb_exec ) ;
	sscanf( tab_arg[3] , "%i" , &nb_proc ) ;
	strcpy( nom_cmd , tab_arg[2] );
	
	for(i=0;i<N;i++)
		tab[i]=0;
		

	
	pipe(tube);
	for (j=0; j<nb_proc; j++){//la boucle d'exécution des commandes
		tab_pid[j]=fork();//mettre les pids de chaque processus dans une liste
		switch (tab_pid[j]) {
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
							fd=open("/dev/null",O_RDWR, 0644 );//redirection des sorties
							close(1);
							dup(fd);
							execlp(nom_cmd,nom_cmd,NULL);
							exit(7);
						default:/*pere*/
							wait(&n);
							if(n!=0){//Quand un fils termine anormalment ou interpreter par un signal
								if(WIFEXITED(n))
									printf("processus %i: Commande se termine anormalement: %i\n",getpid(),WEXITSTATUS(n));
								if(WEXITSTATUS(n)==7)
									printf("erreur de execlp\n");
								if(WIFSIGNALED(n))
									printf("processus %i: Execution terminé par un signal: %d\n",getpid(),WTERMSIG(n));
								exit(2);
							}
							
					}
				}
				exit(0);
		}
		
	}
	while(pid!=-1){//boucle pour recevoir les résultats
		pid=waitpid(-1,&n,WNOHANG);//quand des fils sont fini
		if(n!=0&&pid!=-1&&pid!=0)
			printf("processus :%i pas reussie\n",pid);
		else if(pid==-1)
			printf("fin d'exécution\n");
		else if(pid!=0){//processus termine normalment
			gettimeofday(&end,NULL);
			for (j=0; j<nb_proc; j++){//trouver le pid dans la liste des pids
				if(pid==tab_pid[j]){
					close(tube[1]);
					read(tube[0],&start,sizeof(struct timeval));
					time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
					printf("time_use : %i\n",time_use);
					printf("pid=%i,n=%i\n",pid,n);
					tab[j]=time_use;		
				}
			}
						
						
		}
	}
					
	printf("resultats:\n");//afficher les résultats sans trier
	for (i=0; i<nb_proc; i++) {
		if(tab[i]!=0){
			tab[i]=tab[i]/nb_exec;
			printf("M%i=%i ",i,tab[i]);
		}
	}
	printf("\n");
	
	tri(tab,&nb_proc);//trier des resultats par croissance
	printf("trier:\n");
	for (i=0; i<nb_proc; i++) {
		if(tab[i]!=0){
			printf("M%i=%i ",i,tab[i]);
		}
	}
	printf("\n");//afficher le resultat final
	printf("temps moyenne :");
	if(nb_proc%2!=0)
		printf("%i\n",tab[nb_proc/2]);
	else
		printf("%i\n",(tab[nb_proc/2]+tab[nb_proc/2-1])/2);
}
