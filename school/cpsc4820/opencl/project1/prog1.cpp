#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <CL/cl_ext.h>
#include <CL/cl_gl_ext.h>
#include <CL/cl_platform.h>
#include <CL/opencl.h>
#include "RGU.h"

#define N 5

float vector1[N] = {0.0f,1.0f,2.0f,3.0f,4.0f};
float vector2[N] = {5.0f,6.0f,7.0f,8.0f,9.0f};
float outv[N];
size_t work[1] = {N};


// OpenCL globals.
cl_platform_id myplatform;
cl_context mycontext;
cl_device_id *mydevice;
cl_command_queue mycommandq;
cl_kernel mykernelfunc;
cl_program myprogram;
cl_mem gpuv_in1, gpuv_in2, gpuv_out;

void initCL()
{
int err;
size_t mycontxtsize, kernelsize;
char *kernelsource;
unsigned int gpudevcount;

err = RGUGetPlatformID(&myplatform);

err = clGetDeviceIDs(myplatform,CL_DEVICE_TYPE_GPU,0,NULL,&gpudevcount);

mydevice = new cl_device_id[gpudevcount];
err = clGetDeviceIDs(myplatform,CL_DEVICE_TYPE_GPU,gpudevcount,mydevice,NULL);

cl_context_properties props[] = {CL_CONTEXT_PLATFORM, 
	(cl_context_properties)myplatform, 0};

mycontext = clCreateContext(props,1,&mydevice[0],NULL,NULL,&err);
mycommandq = clCreateCommandQueue(mycontext,mydevice[0],0,&err);

kernelsource = RGULoadProgSource("mydot.cl","", &kernelsize);

myprogram = clCreateProgramWithSource(mycontext,1,
	(const char **)&kernelsource, NULL, NULL);

clBuildProgram(myprogram,0,NULL,NULL,NULL,NULL);

mykernelfunc = clCreateKernel(myprogram,"myvadd",NULL);
}

