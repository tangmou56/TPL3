#define N 50
#include<stdio.h>

void mataff(int mat[][N],int n){
	int i,j;	
	for(i=1;i<=n;i++){
		printf("\n");
		for(j=1;j<=n;j++){
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
	mataff(mat,bufnb);
}


void etale(int mat[][N],int donne[][N],int nb,int res[],int taille){
	int i,j,x=1,y=1,z=1,long_cal=0;
	int cal[100][100];
	for(i=1;i<=nb;i++){
		for(j=1;j<=taille;j++){
			long_cal=long_cal+nb;
			printf("x:%i\n",x);			
			y=x;
			z=1;
			for(x=y;x<=long_cal;x++){
				cal[i][x]=donne[i][j]*mat[i][z];
				z++;
			}

		}
		x=1;
		y=1;
		long_cal=0;
	}

	mataff(cal,taille*nb);


}















void main(){
	int mat[N][N];
	int res[N];
	int donne[N][N]={{1,-1,1},{1,-1,1},{1,1,-1}};
	int nb=8;
	matCre(nb,mat);
	etale(mat,donne,nb,res,3);

}










