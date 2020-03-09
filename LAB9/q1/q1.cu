#include<stdio.h>
#include <stdlib.h>

__global__ void replaceMat(int *mat, int *res){
	int i = blockIdx.x, j = threadIdx.x, n = blockDim.x;
	//res[i*n+j] = mat[i*n+j];
	res[i*n+j] = powf(mat[i*n+j],i+1);
	//for(int p=0;p<i;p++)
		//res[i*n+j] *= mat[i*n+j];
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

	replaceMat<<<m,n>>>(da,dt);

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
