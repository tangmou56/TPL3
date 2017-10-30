#define N 50
#include<stdio.h>

void mataff(int mat[][N],int l,int c){
	int i,j;
	for(i=1;i<=l;i++){
		printf("\n");
		for(j=1;j<=c;j++){
			printf("%i ",mat[i][j]);
		}
	}
	printf("\n");
	
}





void matCre(int nb,int mat[][N]){
	
	int bufnb=nb;
	
	int n=2,i,j,a,x=1,y=1;
	int matpre[N][N];
	for(i=1;i<N;i++){
		for(j=1;j<N;j++){
			mat[i][j]=0;
			matpre[i][j]=0;
		}
	}
	
	mat[1][1]=1;
	matpre[1][1]=1;
	nb=nb/2;
	while(nb!=0){
		x=1;
		y=1;
		for(i=1;i<=n/2;i++){
			for(j=1;j<=n/2;j++){
				mat[i][j]=matpre[x][y];
				y++;
				if(y>n/2){
					y=1;
					x++;
				}
			}
		}
		x=1;
		y=1;
		for(i=1;i<=n/2;i++){
			for(j=n/2+1;j<=n;j++){
				mat[i][j]=matpre[x][y];
				y++;
				if(y>n/2){
					y=1;
					x++;
				}
				
			}
		}
		x=1;
		y=1;
		for(i=n/2+1;i<=n;i++){
			for(j=1;j<=n/2;j++){
				mat[i][j]=matpre[x][y];
				y++;
				if(y>n/2){
					y=1;
					x++;
				}
				
			}
		}
		x=1;
		y=1;
		for(i=n/2+1;i<=n;i++){
			for(j=n/2+1;j<=n;j++){
				mat[i][j]=-matpre[x][y];
				y++;
				if(y>n/2){
					y=1;
					x++;
				}
				
			}
		}
		for(i=1;i<N;i++){
			for(j=1;j<N;j++){
				matpre[i][j]=mat[i][j];
			}
		}
		n=n*2;
		nb=nb/2;
		
	}
	mataff(mat,bufnb,bufnb);
}


void etale(int mat[][N],int donne[][N],int nb,int res[],int nb_donne,int taille_donne){
	int i,j,u,long_cal=0;
	int cal[N][N];
	//TRANSFORMATION DES DONNEES
	for(i=1;i<=nb_donne;i++){
		for(j=1;j<=taille_donne;j++){
			for(u=1;u<=nb;u++){
				long_cal++;
				cal[i][long_cal]=donne[i-1][j-1]*mat[i][u];
			}
			
		}
		long_cal=0;
		
	}
	printf("transformation : \n");
	mataff(cal,nb_donne,taille_donne*nb);
	
	
	//ADITION DES DONNEES TRANSFORME
	for(j=1;j<=taille_donne*nb;j++)
		res[j]=0;
	for(i=1;i<=nb_donne;i++){
		for(j=1;j<=taille_donne*nb;j++){
			res[j]=res[j]+cal[i][j];
		
		
		}
	}
	printf("addition : \n");
	for(j=1;j<=taille_donne*nb;j++)
		printf("%i ",res[j]);
	printf("\n");
	
	
}















void main(){
	int mat[N][N];
	int res[N];
	int donne[N][N]={{1,-1,1},{1,-1,1},{1,1,-1}};
	int nb=8;
	matCre(nb,mat);
	etale(mat,donne,nb,res,3,3);
	
}










