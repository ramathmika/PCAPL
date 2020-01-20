#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int num,rank,size,fact=1,sum=0,i;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int A[size],B[size];

	if(!rank){
		fprintf(stdout, "Enter %d values: ",size);
		for(i=0;i<size;i++)
			scanf("%d",&A[i]);
		fflush(stdout);
	}

	MPI_Scatter(A,1,MPI_INT,&num,1,MPI_INT,0,MPI_COMM_WORLD);

	fprintf(stdout, "Process %d recieved: %d\n",rank,num);
	fflush(stdout);

	for(i=num;i>0;i--)
		fact *= i;

	MPI_Gather(&fact,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank){
		for(i=0;i<size;i++)
			sum += B[i];
		fprintf(stdout, "Sum of factorials of given numbers is: %d\n",sum); 
	}

	MPI_Finalize();
	return 0;
}