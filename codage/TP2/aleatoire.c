
#include <stdio.h>
#define N 1000


/*La structure de polynôme*/
typedef struct{
	int nb;/*Le nombre de champs*/
	int p[N];/*Les valeurs des champs,decroissante de 0 à nb-1*/
}poly_t;




/*trier d'une liste decroissantement*/
void tri(int tab[],int size){
	int i=0,buf;
	while(i<size){
		if(tab[i]<tab[i+1]){
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


/*Tester si une valeur est dans une liste*/
int existe(int n,int l[N],int size){
	int i=0;
	for(i=0;i<size;i++){
		if(l[i]==n)
			return 1;	
	}
	return 0;

}



/*Afficher une liste*/
void print_liste(int l[],int n){
	int i;
	for(i=0;i<n;i++)
		printf("%i ",l[i]);
	printf("\n");

}

/*Afficher une matrice*/
void print_mat(int mat[][N],int l,int c){
	int i,j;
	for(i=0;i<l;i++){
		
		for(j=0;j<c;j++){
			printf("%i ",mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}



/*Copy une liste dans une autre liste*/
void copy_liste(int de[],int a[],int n){
	int i;
	for(i=0;i<n;i++)
		a[i]=de[i];

}

/*Calculer la valeur de 2 pussance n*/
int puss2(int n){
	int i,res=1;
	for(i=0;i<n;i++)
		res=res*2;
	return res;
}



/*Mettre la valeur 'in' dans la 1er position de la séquance 'l',déplacer chaque éléments a droit,est retourne le dernier élément de la séquence*/
int LM(int l[],int in,int n){
	n=n-1;
	int res=l[n-1];
	while(n>0){
		l[n]=l[n-1];
		n--;
	}
	l[0]=in;
	return res;	
}

/*Remplir une liste par 1*/
void remplir(int l[],int n){
	int i;
	for(i=0;i<n;i++)
		l[i]=1;
}


/*Calculer la valeur de entrer de séquence a partir du polynome*/
/*La séquence avance et retourne la valeur sortie*/
int generation(int l[],poly_t poly,int n){
	int i;
	int in=((l[poly.p[0]-1])!=(l[poly.p[1]-1]));
	for(i=2;i<poly.nb;i++){
		in=in!=l[poly.p[i]-1];
	}
	return LM(l,in,n);

}


/*Le générateur de codeur gold*/
void codeur_gold(int res [N],int n,poly_t poly1,poly_t poly2){
	int i,nb_seq=puss2(n)-1;
	int lm1[N];
	int lm2[N];
	remplir(lm1,n);
	remplir(lm2,n);	
	for(i=0;i<nb_seq;i++){
		
		res[i]=generation(lm1,poly1,n)!=generation(lm2,poly2,n);

	}

	
	

}

/*Le générateur de codeur jpl*/
void codeur_jpl(int res[N],int n,poly_t poly1,poly_t poly2,poly_t poly3){
	int i,nb_seq=puss2(n)-1;
	int lm1[N];
	int lm2[N];
	int lm3[N];
	remplir(lm1,n);
	remplir(lm2,n);
	remplir(lm3,n);
	for(i=0;i<nb_seq;i++){
		
		res[i]=generation(lm1,poly1,n)!=generation(lm2,poly2,n);
		res[i]=res[i]!=generation(lm3,poly3,n);
		
	}
	
	
	
	
}

/*Construe d'un polynôme par saisir les valeurs*/
poly_t poly_cons(int n){
	poly_t poly;
	int nb,i;
	int x[n],buf;
	
	printf("Saisir le nombre de champs :");
	scanf("%i",&nb);
	while(nb%2!=0||nb>n-1){
		printf("Invalide,Saisir le nombre de champs :");
		scanf("%i",&nb);
	}
	for(i=0;i<nb;i++){
		printf("Saisir la valeur de champs %i :",i+1);
		scanf("%i",&buf);
		while(buf>n||existe(buf,x,nb)){
			printf("La valeur doit < à %i et > 0 et non répétition :",n);
			scanf("%i",&buf);
		}
		x[i]=buf;

	}
	tri(x,nb);
	printf("Polynôme :");
	print_liste(x,nb);
	copy_liste(x,poly.p,nb);
	for(i=0;i<n;i++)
		poly.p[i]=poly.p[i]-1;
	return poly;
		
}




void main(){
	int n=7,i;
	int nb_seq=puss2(n)-1;
	int lm1[N];
	int res[N][N];
	int res_jpl[N];
	int res_gold[N];
	poly_t poly1;
	poly1.p[0]=6;
	poly1.p[1]=3;
	poly1.p[2]=2;
	poly1.p[3]=1;
	poly1.nb=4;
	poly_t poly2;
	poly2.p[0]=6;
	poly2.p[1]=4;
	poly2.p[2]=3;
	poly2.p[3]=1;
	poly2.nb=4;
	poly_t poly3;
	poly3.p[0]=4;
	poly3.p[1]=3;
	poly3.p[2]=2;
	poly3.p[3]=1;
	poly3.nb=4;
	codeur_gold(res_gold,n,poly1,poly2);
	codeur_jpl(res_jpl,n,poly1,poly2,poly3);
	print_liste(res_jpl,nb_seq);
	print_liste(res_jpl,nb_seq);
	
	/*remplir(lm1,n);
	for(i=0;i<20;i++){
		copy_liste(lm1,res[i],n);
		generation(lm1,poly,n);
		//print_liste(lm1,n);
	}
	print_mat(res,20,n);*/

}
