#define SIG_JEU SIGUSR1
#include<stdio.h>
#include<signal.h>


int main(){
	int pid;
	scanf("%i",&pid);
	kill(pid,SIG_JEU);
}
