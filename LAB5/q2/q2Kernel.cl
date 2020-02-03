__kernel void ones_complement(__global int *A,__global int *B){
	int i = get_global_id(0),rem[10],res,n,k;
	
	n = A[i];
	res = 0;
	k = 0;
	do{
		if(n%10 == 0)
			rem[k] = 1;
		else
			rem[k] = 0;
		n = n/10;
		k = k+1;
	}while(n>0);
	
	for(int j=k-1;j>=0;j--)
		res = res*10 + rem[j];
		
	B[i] = res;
}