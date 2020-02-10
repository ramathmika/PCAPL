__kernel void str_print(__global char *A, __global char *B, int len){
	int id = get_global_id(0),i;
	
	for(i=0;i<len;i++)
		B[id*len + i] = A[i];
}