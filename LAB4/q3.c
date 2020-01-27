#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	int rank,mat[3][3],i,j,x,count=0,B[3],sum;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(!rank){
		fprintf(stdout,"Enter the matrix:\n");
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				scanf("%d",&mat[i][j]);
		fprintf(stdout,"Enter the value to be searched: ");
		fflush(stdout);
		scanf("%d",&x);
	}

	MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(mat,3,MPI_INT,B,3,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0;i<3;i++)
		if(B[i] == x)
			count++;

	MPI_Reduce(&count,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(!rank)
		fprintf(stdout, "Number of occurences: %d\n",sum);

	MPI_Finalize();
	return 0;

}