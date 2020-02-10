#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(){

	int n,i,*arr;

	printf("Enter the number of elements: ");
	scanf("%d",&n);

	arr = (int *)malloc(n*sizeof(int));

	printf("Enter the array: ");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("q2Kernel.cl","r");

	if(!fp){
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}

	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);
	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint num_devices,num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&num_devices);

	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	cl_command_queue cmdq = clCreateCommandQueue(context,device_id,CL_QUEUE_PROFILING_ENABLE,&ret);

	cl_mem abuff = clCreateBuffer(context,CL_MEM_READ_ONLY,n*sizeof(int),NULL,&ret);

	cl_mem bbuff = clCreateBuffer(context,CL_MEM_WRITE_ONLY,n*sizeof(int),NULL,&ret);

	ret = clEnqueueWriteBuffer(cmdq,abuff,CL_TRUE,0,n*sizeof(int),arr,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char **)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"selectionSort",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&abuff);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&bbuff);

	size_t global_item_size = n, local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(cmdq,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,&event);




	int *B = (int *)malloc(sizeof(int)*n);

	ret = clEnqueueReadBuffer(cmdq,bbuff,CL_TRUE,0,n*sizeof(int),B,0,NULL,NULL);

	printf("\nSorted array is: ");
	for(i=0;i<n;i++)
		printf("%d ",B[i]);

	ret = clFinish(cmdq);

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(abuff);
	ret = clReleaseMemObject(bbuff);
	ret = clReleaseCommandQueue(cmdq);
	ret = clReleaseContext(context);

	free(B);
	return 0;

}
