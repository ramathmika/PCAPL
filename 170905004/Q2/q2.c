#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int rank;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	fprintf(stdout,"Rank: %d\n",rank);

	if(rank%2==0)
		fprintf(stdout,"Hello\n");
	else
		fprintf(stdout,"World\n");
	fflush(stdout);

	MPI_Finalize();
	return 0;
}
