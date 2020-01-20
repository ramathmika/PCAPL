#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int m,rank,size,i,A[100],recv[100];
	float avg,B[100],tavg, sum=0, tsum=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank){
		fprintf(stdout, "Enter value for m: ");
		scanf("%d",&m);
		fprintf(stdout, "Enter %d values: ",size*m);
		for(i=0;i<(size*m);i++)
			scanf("%d",&A[i]);
		fflush(stdout);
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(A,m,MPI_INT,recv,m,MPI_INT,0,MPI_COMM_WORLD);

	fprintf(stdout, "Process %d recieved: ",rank);
	fflush(stdout);

	for(i=0;i<m;i++){
		fprintf(stdout, "%d ",recv[i]);
		sum += recv[i];
	}
	fflush(stdout);
	avg = (float)sum/m;
	fprintf(stdout, "\nProcess %d average is %f\n",rank,avg);
	fflush(stdout);

	MPI_Gather(&avg,1,MPI_FLOAT,B,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(!rank){
		for(i=0;i<size;i++)
			tsum += B[i];
		tavg = (float)tsum/size;

		fprintf(stdout, "\nTotal average is: %f\n",tavg);
	}

	MPI_Finalize();
	return 0;

}