__kernel void selectionSort(__global int *A, __global int *B){
	int id = get_global_id(0),n = get_global_size(0),i,pos=0;
	
	for(i=0;i<n;i++)
		if((A[i]<A[id]) || (A[i] == A[id] && i<id))
			pos++;
	
	B[pos] = A[id];
	
} 