#define SIG_JEU SIGUSR1
#include<stdio.h>
#include<signal.h>


int main(){
	int pid,i;
	scanf("%i",&pid);
	kill(pid,SIG_JEU);
	scanf("%i",&i);
	kill(pid,SIG_JEU);
	//sleep(1);
	//kill(pid,SIGUSR2);
	//sleep(1);
	//ååkill(pid,SIGUSR2);
}
