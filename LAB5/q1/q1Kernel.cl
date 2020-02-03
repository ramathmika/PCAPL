__kernel void dec_to_octal(__global int *A,__global int *B){
	int i = get_global_id(0),rem[10],res,n,k;
	
	n = A[i];
	res = 0;
	k = 0;
	while(n>0){
		rem[k] = n%8;
		n = n/8;
		k = k+1;
	}
	
	for(int j=k-1;j>=0;j--)
		res = res*10 + rem[j];
		
	B[i] = res;
}