all : aleatoire.o hada.o prog_alea prog_hada

aleatoire.o : aleatoire.c
	gcc -c aleatoire.c


hada.o : hada.c
	gcc -c hada.c


prog_alea : aleatoire.o
	gcc -o prog_alea aleatoire.o


prog_hada : hada.o
	gcc -o prog_hada hada.o


clean :
	rm *.o