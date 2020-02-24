#include <stdio.h>

__global__ void vecAdd1(int *A, int *B,int *C){
	int id = blockIdx.x;
	C[id] = A[id] + B[id];
}

__global__ void vecAdd2(int *A, int *B, int *C){
	int id = threadIdx.x;
	C[id] = A[id] + B[id];
}

__global__ void vecAdd3(int *A, int *B, int *C){
	int id = blockIdx.x*blockDim.x + threadIdx.x;
	C[id] = A[id] + B[id];
}

int main(){
	int A[100],B[100],C[100],n,i,size;

	printf("Enter value for n: ");
	scanf("%d",&n);

	printf("Enter the values for vector A:\n");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	printf("Enter the values for vector B:\n");
	for(i=0;i<n;i++)
		scanf("%d",&B[i]);

	int *da, *db, *dc;
	size = sizeof(int)*n;

	cudaMalloc((void **)&da,size);
	cudaMalloc((void**)&db,size);
	cudaMalloc((void **)&dc,size);

	cudaMemcpy(da,A,size,cudaMemcpyHostToDevice);
	cudaMemcpy(db,B,size,cudaMemcpyHostToDevice);


	printf("Result through %d blocks:\n",n);
	vecAdd1<<<n,1>>>(da,db,dc);

	cudaMemcpy(C,dc,size,cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
		printf("%d ",C[i]);

	printf("\nResult through %d threads:\n",n);
	vecAdd2<<<1,n>>>(da,db,dc);

	cudaMemcpy(C,dc,size,cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
		printf("%d ",C[i]);

	printf("\nResult through varying block size:\n");
	vecAdd3<<<ceil(n/3),3>>>(da,db,dc);

	cudaMemcpy(C,dc,size,cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
		printf("%d ",C[i]);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	return 0;
}
