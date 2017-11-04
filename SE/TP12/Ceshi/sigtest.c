#define SIG_JEU SIGUSR1
#include<stdio.h>
#include<signal.h>

static void handler(int sig,siginfo_t *siginfo){
	int i;
	printf("handled\n");
	printf("pid :%d\n",siginfo->si_pid);
	scanf("%i",&i);
	signal(SIG_JEU,handler);
}

static void handler2(int sig,siginfo_t *siginfo){
	
	printf("handled 2\n");
	printf("pid :%d\n",siginfo->si_pid);

}

int main(){
	struct sigaction act;
	struct sigaction act2;
	act2.sa_sigaction=handler2;
	act.sa_sigaction=handler;
	//act.sa_flags=SA_NODEFER;
	act.sa_flags=0;
	act2.sa_flags=SA_SIGINFO;
	//sigemptyset(&act.sa_mask);
	//sigaddset(&act.sa_mask,SIGUSR2);
	sigaction(SIG_JEU,&act,NULL);
	sigaction(SIGUSR2,&act2,NULL);
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
