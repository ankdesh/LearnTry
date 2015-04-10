#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <math.h>

#include "bmpfuncs.h"

#define PLATFORM_TO_USE 0

// This function takes a positive integer and rounds it up to
// the nearest multiple of another provided integer
unsigned int roundUp(unsigned int value, unsigned int multiple) {

  // Determine how far past the nearest multiple the value is
  unsigned int remainder = value % multiple;

  // Add the difference to make the value a multiple
  if(remainder != 0) {
          value += (multiple-remainder);
  }

  return value;
}

// This function reads in a text file and stores it as a char pointer
char* readSource(char* kernelPath) {

   cl_int status;
   FILE *fp;
   char *source;
   long int size;

   printf("Program file is: %s\n", kernelPath);

   fp = fopen(kernelPath, "rb");
   if(!fp) {
      printf("Could not open kernel file\n");
      exit(-1);
   }
   status = fseek(fp, 0, SEEK_END);
   if(status != 0) {
      printf("Error seeking to end of file\n");
      exit(-1);
   }
   size = ftell(fp);
   if(size < 0) {
      printf("Error getting file position\n");
      exit(-1);
   }

   rewind(fp);

   source = (char *)malloc(size + 1);

   int i;
   for (i = 0; i < size+1; i++) {
      source[i]='\0';
   }

   if(source == NULL) {
      printf("Error allocating space for the kernel source\n");
      exit(-1);
   }

   fread(source, 1, size, fp);
   source[size] = '\0';

   return source;
}

void chk(cl_int status, const char* cmd) {

   if(status != CL_SUCCESS) {
      printf("%s failed (%d)\n", cmd, status);
      exit(-1);
   }
}

int main() {

   // Set the image rotation (in degrees)
   float theta = 3.14159/6;
   float cos_theta = cosf(theta);
   float sin_theta = sinf(theta);
   printf("theta = %f (cos theta = %f, sin theta = %f)\n", theta, cos_theta, 
      sin_theta);

   // Rows and columns in the input image
   int imageHeight;
   int imageWidth;

   const char* inputFile = "input.bmp";
   const char* outputFile = "output.bmp";

   // Homegrown function to read a BMP from file
   float* inputImage = readImage(inputFile, &imageWidth,
      &imageHeight);

   // Size of the input and output images on the host
   int dataSize = imageHeight*imageWidth*sizeof(float);

   // Output image on the host
   float* outputImage = NULL;
   outputImage = (float*)malloc(dataSize);

   // Set up the OpenCL environment
   cl_int status;

   // Discovery platform
   cl_platform_id platforms[2];
   cl_platform_id platform;
   status = clGetPlatformIDs(2, platforms, NULL);
   chk(status, "clGetPlatformIDs");
   platform = platforms[PLATFORM_TO_USE];

   // Discover device
   cl_device_id device;
   clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
   chk(status, "clGetDeviceIDs");

   // Create context
   cl_context_properties props[3] = {CL_CONTEXT_PLATFORM,
       (cl_context_properties)(platform), 0};
   cl_context context;
   context = clCreateContext(props, 1, &device, NULL, NULL, &status);
   chk(status, "clCreateContext");

   // Create command queue
   cl_command_queue queue;
   queue = clCreateCommandQueue(context, device, 0, &status);
   chk(status, "clCreateCommandQueue");

   // Create the input and output buffers
   cl_mem d_input;
   d_input = clCreateBuffer(context, CL_MEM_READ_ONLY, dataSize, NULL,
       &status);
   chk(status, "clCreateBuffer");

   cl_mem d_output;
   d_output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, dataSize, NULL,
       &status);
   chk(status, "clCreateBuffer");

   // Copy the input image to the device
   status = clEnqueueWriteBuffer(queue, d_input, CL_TRUE, 0, dataSize, 
         inputImage, 0, NULL, NULL);
   chk(status, "clEnqueueWriteBuffer");

   const char* source = readSource("rotation.cl");

   // Create a program object with source and build it
   cl_program program;
   program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
   chk(status, "clCreateProgramWithSource");
   status = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
   chk(status, "clBuildProgram");
   
   // Create the kernel object
   cl_kernel kernel;
   kernel = clCreateKernel(program, "img_rotate", &status);
   chk(status, "clCreateKernel");

   // Set the kernel arguments
   status  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_output);
   status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_input);
   status |= clSetKernelArg(kernel, 2, sizeof(int), &imageWidth);
   status |= clSetKernelArg(kernel, 3, sizeof(int), &imageHeight);
   status |= clSetKernelArg(kernel, 4, sizeof(float), &sin_theta);
   status |= clSetKernelArg(kernel, 5, sizeof(float), &cos_theta);
   chk(status, "clSetKernelArg");

   // Set the work item dimensions
   size_t globalSize[2] = {imageWidth, imageHeight};
   status = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalSize, NULL, 0,
      NULL, NULL);
   chk(status, "clEnqueueNDRange");

   // Read the image back to the host
   status = clEnqueueReadBuffer(queue, d_output, CL_TRUE, 0, dataSize, 
         outputImage, 0, NULL, NULL); 
   chk(status, "clEnqueueReadBuffer");

   // Write the output image to file
   storeImage(outputImage, outputFile, imageHeight, imageWidth, inputFile);

   return 0;
}
