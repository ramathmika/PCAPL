#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int rank, size;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	fprintf(stdout,"Rank: %d.\nSize: %d\n",rank,size);
	fflush(stdout);
	MPI_Finalize();
	return 0;
}
