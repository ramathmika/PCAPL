#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int n,rank,size,i,arr1[100],arr2[100],rarr[100],ns;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank){
		fprintf(stdout, "Enter the size of the array: ");
		scanf("%d",&n);
		fprintf(stdout, "Enter the values:\n");
		for(i=0;i<n;i++)
			scanf("%d",&arr1[i]);
		fflush(stdout);
		ns = n/4;
	}

	MPI_Bcast(&ns,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(arr1,ns,MPI_INT,rarr,ns,MPI_INT,0,MPI_COMM_WORLD);

	for(i=1;i<ns;i++)
		rarr[i] += rarr[i-1];

	MPI_Gather(rarr,ns,MPI_INT,arr2,ns,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank){
		fprintf(stdout, "Resultant array is: \n");
		for(i=0;i<n;i++)
			fprintf(stdout, "%d ",arr2[i]);
		fflush(stdout);
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}