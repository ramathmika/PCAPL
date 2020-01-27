#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank,size;

	MPI_Init(&argc,&argv);
	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int err_code,len,err_class;
	char err_string[100];

	err_code = MPI_Comm_size(7,&size);

	if(err_code != MPI_SUCCESS){
		// MPI_Error_string(err_code,err_string,&len);
		// fprintf(stdout, "Code: %s\n",err_string);
		MPI_Error_class(err_code,&err_class);
		MPI_Error_string(err_class,err_string,&len);
		
	}

	if(!rank){
		fprintf(stdout, "Class: %s\n",err_string);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}