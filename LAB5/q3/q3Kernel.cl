__kernel void swap(__global int *A){
	int i = get_global_id(0)*2,temp;
	
	temp = A[i];
	A[i] = A[i+1];
	A[i+1] = temp;
}