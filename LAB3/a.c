#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	int rank,size,i,len,n,nvow=0,count[100],sum=0,ascii[100],rascci[100];
	char str[100], rstr[100], str2[100];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank){
		fprintf(stdout, "Enter a string such that the length is divisible by %d: ",size);
		scanf("%s",str);
		len = strlen(str);
		fflush(stdout);
		n = len/size;
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(str,n,MPI_CHAR,rstr,n,MPI_CHAR,0,MPI_COMM_WORLD);

	for(i=0;i<n;i++){
		if(rstr[i] >= 'a' && rstr[i] <= 'z')
			rstr[i] -= 32;
		else 
			rstr[i] += 32;
		ascii[i] = (int)rstr[i];
	}

	MPI_Gather(rstr,n,MPI_CHAR,str2,n,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Gather(ascii,n,MPI_INT,rascci,n,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank){
		fprintf(stdout, "Toggled string %s\nToggled char ascii value:\n",str2);

		for(i=0;i<len;i++)
			fprintf(stdout, "%d ",rascci[i]);

		fflush(stdout);
	}

	printf("\n");

	MPI_Finalize();
	return 0;

}