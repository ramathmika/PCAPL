#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void transpose(int *a, int *t){
	int n = threadIdx.x, m = blockIdx.x, size = blockDim.x, size1 = gridDim.x;
	t[n*size1+m] = a[m*size+n];
}

int main(){
	int *a,*t,m,n,i,j,*da,*dt;
	printf("Enter m: ");
	scanf("%d",&m);
	printf("Enter n: ");
	scanf("%d",&n);

	int size = sizeof(int)*m*n;

	a = (int *)malloc(size);
	t = (int *)malloc(size);

	printf("Enter the matrix:\n");
	for(i=0;i<m*n;i++)
		scanf("%d",&a[i]);

	cudaMalloc((void **)&da,size);
	cudaMalloc((void **)&dt,size);

	cudaMemcpy(da,a,size,cudaMemcpyHostToDevice);

	transpose<<<m,n>>>(da,dt);

	cudaMemcpy(t,dt,size,cudaMemcpyDeviceToHost);

	printf("Result:\n");

	for(i=0;i<n;i++){
		for(j=0;j<m;j++)
			printf("%d ",t[i*m+j]);
		printf("\n");
	}

	cudaFree(da);
	cudaFree(dt);
	return 0;
}
