#include <stdio.h>

__global__ void matrixSort(int *A, int *B){
	int id = blockIdx.x*blockDim.x + threadIdx.x,m = gridDim.x,pos=0;
	for(int i=0;i<m;i++)
		if(A[id]>A[i] || (A[i]==A[id] && i<id))
			pos++;
	B[pos] = A[id];

}


int main(){
	int A[100][100],B[100],m,n,i,j,size;

	printf("Enter value for n,m: ");
	scanf("%d %d",&n,&m);

	printf("Enter the values for matrix :\n");
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%d",&A[i][j]);


	int *da,*db;
	size = sizeof(int)*n*m;

	cudaMalloc((void **)&da,size);
	cudaMalloc((void**)&db,size/n);

	cudaMemcpy(da,A,size,cudaMemcpyHostToDevice);


	printf("Result:\n");
	for(i=0;i<n;i++){
		matrixSort<<<n,m>>>(da,db);

		cudaMemcpy(B,db,size,cudaMemcpyDeviceToHost);
		for(j=0;j<m;j++)
			printf("%d ",B[i]);
		printf("\n");
	}



	cudaFree(da);
	cudaFree(db);
	return 0;
}
