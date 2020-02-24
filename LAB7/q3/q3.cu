#include <stdio.h>

__global__ void vecAdd(int *X, int *Y, int a, int *F){
	int id = threadIdx.x;
	F[id] = a*X[id] + Y[id];
}

int main(){
	int i,n,a,X[100],Y[100],F[100],*dx,*dy,*df;

	printf("Enter value for a: ");
		scanf("%d",&a);

	printf("Enter value for n: ");
	scanf("%d",&n);

	printf("Enter the values for vector X:\n");
	for(i=0;i<n;i++)
		scanf("%d",&X[i]);
	printf("Enter the values for vector Y:\n");
	for(i=0;i<n;i++)
		scanf("%d",&Y[i]);

	int size = sizeof(int)*n;

	cudaMalloc((void **)&dx,size);
	cudaMalloc((void **)&dy,size);
	cudaMalloc((void **)&df,size);

	cudaMemcpy(dx,X,size,cudaMemcpyHostToDevice);
	cudaMemcpy(dy,Y,size,cudaMemcpyHostToDevice);

	vecAdd<<<1,n>>>(dx,dy,a,df);

	cudaMemcpy(F,df,size,cudaMemcpyDeviceToHost);

	printf("Result: ");
	for(i=0;i<n;i++)
		printf("%d ",F[i]);

	cudaFree(dx);
	cudaFree(dy);
	cudaFree(df);

	return 0;
}
