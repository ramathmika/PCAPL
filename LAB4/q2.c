#include <stdio.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char*argv[]){
	int rank,size;
	float psum,sum;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	psum = (float)(4/(1+(pow(((rank+0.5)/size),2)))) * (1/(float)size);

	MPI_Reduce(&psum,&sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

	if(!rank){
		printf("Value of pi calculated is %f\n",sum);
	}

	MPI_Finalize();
	return 0;
}