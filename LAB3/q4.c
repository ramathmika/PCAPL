#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int rank,size,i,len,n,k=0;
	char s1[100], s2[100], rs1[100], rs2[100], str1[100], str2[100];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank){
		fprintf(stdout, "Enter two strings such that their lengths are divisible by %d: ",size);
		scanf("%s %s",s1,s2);
		len = strlen(s1);
		fflush(stdout);
		n = len/size;
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(s1,n,MPI_CHAR,rs1,n,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(s2,n,MPI_CHAR,rs2,n,MPI_CHAR,0,MPI_COMM_WORLD);

	for(i=0;i<n;i++){
		str1[k++] = rs1[i];
		str1[k++] = rs2[i];
	}
	str1[k] = '\0';

	MPI_Gather(str1,2*n,MPI_CHAR,str2,2*n,MPI_CHAR,0,MPI_COMM_WORLD);

	if(!rank){
		fprintf(stdout, "\nResultant string is: %s\n",str2);
	}

	MPI_Finalize();
	return 0;

}
