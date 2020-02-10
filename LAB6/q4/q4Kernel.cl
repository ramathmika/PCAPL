__kernel void str_rev(__global char *A, __global char *B, __global int *I){
	int id = get_global_id(0),i,k=0;
	
	for(i=L[id]-1;i>=0 && A[i-1]!=' ';i--){
		if(id==0)
			B[k] = A[i];
		else
			B[I[id]+1+k] = A[i];
		k++;
	}

	
}