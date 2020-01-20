#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isvowel(char c){
	switch(tolower(c)){
		case 'a': case 'e': case 'i': case'o': case'u': return 1;
		default: return 0;
	}
}

int main(int argc, char *argv[]){
	int rank,size,i,len,n,nvow=0,count[100],sum=0;
	char str[100], rstr[100];

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

	for(i=0;i<n;i++)
		if(!isvowel(rstr[i]))
			nvow++;

	MPI_Gather(&nvow,1,MPI_INT,count,1,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank){
		for(i=0;i<size;i++){
			fprintf(stdout, "\nProcess %d found %d non-vowels.\n",i,count[i]);
			sum += count[i];
		}

		fflush(stdout);
		fprintf(stdout, "\nTotal non-vowels are: %d\n",sum);
	}

	MPI_Finalize();
	return 0;

}