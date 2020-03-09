#include <stdio.h>
#include <stdlib.h>

__global__ void mul1(int *A, int *B, int *C, int n, int q){
	int id = threadIdx.x, i,j;
	for(i=0;i<q;i++){
		C[id*q+i] = 0;
		for(j=0;j<n;j++)
			C[id*q+i] += A[id*n+j] * B[j*q+i];
	}
}

__global__ void mul2(int *A, int *B, int *C, int m, int q){
	int id = threadIdx.x, i, j, n = blockDim.x;
	for(i=0;i<m;i++){
		C[i*q+id] = 0;
		for(j=0;j<n;j++)
			C[i*q+id] += A[i*n+j] * B[j*q+id];
	}
}

__global__ void mul3(int *A, int *B, int *C, int n){
	int bid = blockIdx.x, tid = threadIdx.x, q = blockDim.x,i;
	C[bid*q+tid] = 0;
	for(i=0;i<n;i++)
		C[bid*q+tid] += A[bid*n+i] * B[i*q+tid];
}

int main(){
	int *a,*b,*c,*da,*db,*dc,m,n,p,q,i,j;

	printf("Enter m: ");
	scanf("%d",&m);
	printf("Enter n: ");
	scanf("%d",&n);

	int size1 = sizeof(int)*m*n;

	a = (int *)malloc(size1);

	printf("Enter first matrix:\n");
	for(i=0;i<m*n;i++)
		scanf("%d",&a[i]);


	printf("Enter p: ");
	scanf("%d",&p);
	printf("Enter q: ");
	scanf("%d",&q);

	int size2 = sizeof(int)*p*q;

	b = (int *)malloc(size2);

	printf("Enter second matrix:\n");
	for(i=0;i<p*q;i++)
		scanf("%d",&b[i]);

	if(n!=p){
		printf("%d != %d. Cannot multiply.\n",n,p);
		exit(0);
	}

	int size3 = sizeof(int)*m*q;
	c = (int *)malloc(size3);

	cudaMalloc((void **)&da,size1);
	cudaMalloc((void **)&db,size2);
	cudaMalloc((void **)&dc,size3);

	cudaMemcpy(da,a,size1,cudaMemcpyHostToDevice);
	cudaMemcpy(db,b,size2,cudaMemcpyHostToDevice);

	printf("Result 1)Thread per row:\n");

	mul1<<<1,m>>>(da,db,dc,n,q);

	cudaMemcpy(c,dc,size3,cudaMemcpyDeviceToHost);

	for(i=0;i<m;i++){
		for(j=0;j<q;j++)
			printf("%d ",c[i*q+j]);
		printf("\n");
	}

	printf("Result 2)Thread per column:\n");

	mul2<<<1,n>>>(da,db,dc,m,q);

	cudaMemcpy(c,dc,size3,cudaMemcpyDeviceToHost);

	for(i=0;i<m;i++){
		for(j=0;j<q;j++)
			printf("%d ",c[i*q+j]);
		printf("\n");
	}

	printf("Result 3)Thread per element:\n");

	mul3<<<m,q>>>(da,db,dc,n);

	cudaMemcpy(c,dc,size3,cudaMemcpyDeviceToHost);

	for(i=0;i<m;i++){
		for(j=0;j<q;j++)
			printf("%d ",c[i*q+j]);
		printf("\n");
	}

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	return 0;


}
