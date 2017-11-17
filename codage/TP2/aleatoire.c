
#include <stdio.h>
#define N 1000

typedef struct{

/*	int p1;
	int p2;*/
	int nb;
	int p[N];


}poly_t;
void print_liste(int l[],int n){
	int i;
	for(i=0;i<n;i++)
		printf("%i ",l[i]);
	printf("\n");

}

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




void copy_liste(int de[],int a[],int n){
	int i;
	for(i=0;i<n;i++)
		a[i]=de[i];

}

int puss2(int n){
	int i,res=1;
	for(i=0;i<n;i++)
		res=res*2;
	return res;
}

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

void remplir(int l[],int n){
	int i;
	for(i=0;i<n;i++)
		l[i]=1;
}

int generation(int l[],poly_t poly,int n){
	int i;
	int in=((l[poly.p[0]-1])!=(l[poly.p[1]-1]));
	for(i=2;i<poly.nb;i++){
		in=in!=l[poly.p[i]-1];
	}
	return LM(l,in,n);

}


void codeur_gold(int n,poly_t poly1,poly_t poly2){
	int i,ran[N],nb_seq=puss2(n)-1;
	int lm1[N];
	int lm2[N];
	remplir(lm1,n);
	remplir(lm2,n);	
	for(i=0;i<nb_seq;i++){
		
		ran[i]=generation(lm1,poly1,n)!=generation(lm2,poly2,n);

	}

	print_liste(ran,nb_seq);
	

}


void codeur_jpl(int n,poly_t poly1,poly_t poly2,poly_t poly3){
	int i,ran[N],nb_seq=puss2(n)-1;
	int lm1[N];
	int lm2[N];
	int lm3[N];
	remplir(lm1,n);
	remplir(lm2,n);
	remplir(lm3,n);
	for(i=0;i<nb_seq;i++){
		
		ran[i]=generation(lm1,poly1,n)!=generation(lm2,poly2,n);
		ran[i]=ran[i]!=generation(lm3,poly3,n);
		
	}
	
	print_liste(ran,nb_seq);
	
	
}







void main(){
	int n=7,i;
	int lm1[N];
	int res[N][N];
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
	codeur_gold(n,poly1,poly2);
	codeur_jpl(n,poly1,poly2,poly3);
	/*remplir(lm1,n);
	for(i=0;i<20;i++){
		copy_liste(lm1,res[i],n);
		generation(lm1,poly,n);
		//print_liste(lm1,n);
	}
	print_mat(res,20,n);*/

}
