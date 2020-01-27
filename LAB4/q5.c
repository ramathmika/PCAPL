#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank,i,j,mat[4][4],recv[4],out[4][4];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(!rank){
		fprintf(stdout, "Enter the  matrix:\n");
		fflush(stdout);
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				scanf("%d",&mat[i][j]);
	}

	for(i=0;i<4;i++)
		MPI_Scatter(&mat[i][0],1,MPI_INT,&recv[i],1,MPI_INT,0,MPI_COMM_WORLD);

	for(i=1;i<4;i++)
		recv[i] += recv[i-1];

	for(i=0;i<4;i++)
		MPI_Gather(&recv[i],1,MPI_INT,&out[i][0],1,MPI_INT,0,MPI_COMM_WORLD);	

	if(!rank){
		fprintf(stdout,"\nOutput matrix:\n");
		for(i=0;i<4;i++){
			for(j=0;j<4;j++)
				fprintf(stdout,"%d ",out[i][j]);
			printf("\n");
			fflush(stdout);
		}
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}