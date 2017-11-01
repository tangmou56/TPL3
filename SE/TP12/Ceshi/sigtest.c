#define SIG_JEU SIGUSR1
#include<stdio.h>
#include<signal.h>

static void handler(int sig,siginfo_t *siginfo){
	printf("handled\n");
	printf("pid :%d\n",siginfo->si_pid);
	signal(SIG_JEU,handler);
}

int main(){
	struct sigaction act;
	act.sa_sigaction=handler;
	sigaction(SIG_JEU,&act,NULL);
	printf("%i \n",SIGUSR1);
	while(1){
		printf("1\n");
		sleep(1);
		printf("2\n");
		sleep(1);
		printf("3\n");
		sleep(1);
		printf("4\n");
		sleep(1);
	}
}
