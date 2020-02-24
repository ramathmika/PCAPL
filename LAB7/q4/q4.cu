#include <stdio.h>

__global__ void vecSine(float *A, float *B){
	int id = blockIdx.x;
	B[id] = sin(A[id]);
}


int main(){
	float A[100],B[100];
	int n,i,size;

	printf("Enter value for n: ");
	scanf("%d",&n);

	printf("Enter the values for vector A in radians :\n");
	for(i=0;i<n;i++)
		scanf("%f",&A[i]);


	float *da,*db;
	size = sizeof(float)*n;

	cudaMalloc((void **)&da,size);
	cudaMalloc((void**)&db,size);

	cudaMemcpy(da,A,size,cudaMemcpyHostToDevice);


	printf("Result: ");
	vecSine<<<n,1>>>(da,db);

	cudaMemcpy(B,db,size,cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
		printf("%f ",B[i]);


	cudaFree(da);
	cudaFree(db);
	return 0;
}
