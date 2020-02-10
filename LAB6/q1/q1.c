#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(){

	char str[100];

	int n;
	cl_int len,rlen;

	printf("Enter the string: ");
	gets(str);

	printf("Enter the value of n: ");
	scanf("%d",&n);

	len = strlen(str);
//	len++;
	rlen = len*n;

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("q1Kernel.cl","r");

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

	cl_mem sbuff = clCreateBuffer(context,CL_MEM_READ_ONLY,len*sizeof(char),NULL,&ret);
	cl_mem tbuff = clCreateBuffer(context,CL_MEM_WRITE_ONLY,rlen*sizeof(char),NULL,&ret);

	ret = clEnqueueWriteBuffer(cmdq,sbuff,CL_TRUE,0,len*sizeof(char),str,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char **)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"str_print",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&sbuff);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&tbuff);
	ret = clSetKernelArg(kernel,2,sizeof(cl_int),(void *)&len);

	size_t global_item_size = n, local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(cmdq,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,&event);


	ret = clFinish(cmdq);

	char *strres = (char *)malloc(sizeof(char)*rlen);

	ret = clEnqueueReadBuffer(cmdq,tbuff,CL_TRUE,0,rlen*sizeof(char),strres, 0, NULL,NULL);

	strres[rlen] = '\0';
	printf("\nResultant string is: %s",strres);
	getchar();

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(sbuff);
	ret = clReleaseMemObject(tbuff);
	ret = clReleaseCommandQueue(cmdq);
	ret = clReleaseContext(context);

	free(strres);
	return 0;

}
