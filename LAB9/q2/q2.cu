#include <stdio.h>
#include <stdlib.h>

__global__ void add1(int *A, int *B, int *C, int n){
	int id = threadIdx.x, i;
	for(i=0;i<n;i++){
		C[id*n+i] = A[id*n+i] + B[id*n+i];
	}
}

__global__ void add2(int *A, int *B, int *C, int m){
	int id = threadIdx.x, i, n = blockDim.x;
	for(i=0;i<m;i++)
		C[i*n+id] = A[i*n+id] + B[i*n+id];
}

__global__ void add3(int *A, int *B, int *C){
	int i = blockIdx.x, j = threadIdx.x, n = blockDim.x;
	C[i*n+j] = A[i*n+j] + B[i*n+j];
}

int main(){
	int *a,*b,*c,*da,*db,*dc,m,n,i,j;

	printf("Enter m: ");
	scanf("%d",&m);
	printf("Enter n: ");
	scanf("%d",&n);

	int size = sizeof(int)*m*n;

	a = (int *)malloc(size);
	b = (int *)malloc(size);
	c = (int *)malloc(size);

	printf("Enter first matrix:\n");
	for(i=0;i<m*n;i++)
		scanf("%d",&a[i]);

	printf("Enter second matrix:\n");
	for(i=0;i<m*n;i++)
		scanf("%d",&b[i]);

	cudaMalloc((void **)&da,size);
	cudaMalloc((void **)&db,size);
	cudaMalloc((void **)&dc,size);

	cudaMemcpy(da,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(db,b,size,cudaMemcpyHostToDevice);

	printf("Result 1)Thread per row:\n");

	add1<<<1,m>>>(da,db,dc,n);

	cudaMemcpy(c,dc,size,cudaMemcpyDeviceToHost);

	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%d ",c[i*n+j]);
		printf("\n");
	}

	printf("Result 2)Thread per column:\n");

	add2<<<1,n>>>(da,db,dc,m);

	cudaMemcpy(c,dc,size,cudaMemcpyDeviceToHost);

	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%d ",c[i*n+j]);
		printf("\n");
	}

	printf("Result 3)Thread per element:\n");

	add3<<<m,n>>>(da,db,dc);

	cudaMemcpy(c,dc,size,cudaMemcpyDeviceToHost);

	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%d ",c[i*n+j]);
		printf("\n");
	}


	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	return 0;


}
