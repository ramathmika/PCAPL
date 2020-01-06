#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void Prime(int l, int m){
	int i,j,flag;
	fprintf(stdout,"Prime numbers between %d and %d are:\n",l,m);
	for(i=l;i<=m;i++){
		flag = 1;
		for(j=2;j<=i/2;j++)
			if(i%j==0){
				flag = 0;
				break;
			}
		if(flag && i!=1)
			fprintf(stdout,"%d\n",i);
	}
	fflush(stdout);
}

int main(int argc,char *argv[]){
	int rank;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){
		Prime(1,50);
	}
	else{
		Prime(51,100);
	}

	fflush(stdout);

	MPI_Finalize();

	return 0;
}
