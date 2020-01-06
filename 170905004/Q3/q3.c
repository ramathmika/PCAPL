#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	int rank;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int a=5,b=4;
	switch(rank){
		case 0: fprintf(stdout,"Addition: %d + %d = %d\n",a,b,a+b);
				break;
		case 1: fprintf(stdout,"Subtraction: %d - %d = %d\n",a,b,a-b);
				break;
		case 2: fprintf(stdout,"Multiplication: %d * %d = %d\n",a,b,a*b);
				break;
		case 3: fprintf(stdout,"Division: %d / %d = %d\n",a,b,a/b);
				break;
	}

	fflush(stdout);
	MPI_Finalize();
	return 0;

}
