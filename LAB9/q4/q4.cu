#include <stdio.h>
#include <stdlib.h>

__global__ void complement(int *A, int *B){
	int i = blockIdx.x, j = threadIdx.x, m = gridDim.x, n = blockDim.x,k=1,temp,t=0,rev;
	if(i!=0 && i!=m-1 && j!=0 && j!=n-1){
		temp = A[i*n+j];
		do{
			t = t*10 + !(temp%2);
			temp /= 2;
		}while(temp>0);
		do{
			temp = t%10;
			rev = rev*10 + temp;
			t /= 10;
		}while(t>0);
		B[i*n+j] = rev;
	}
	else
		B[i*n+j] = A[i*n+j];
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

	complement<<<m,n>>>(da,dt);

	cudaMemcpy(t,dt,size,cudaMemcpyDeviceToHost);

	printf("Result:\n");

	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%d ",t[i*n+j]);
		printf("\n");
	}

	cudaFree(da);
	cudaFree(dt);
	return 0;
}

