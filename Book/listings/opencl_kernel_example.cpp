// Build program object and set up kernel arguments
const char* source = "__kernel void dp_mul(__global const float *a,\n"
                     "                     __global const float *b,\n"
                     "                     __global float *c,\n"
                     "                     int *N) \n"
                     "{\n"
                     "     int id = get_global_id(0);\n"
                     "     if (id < N)\n"
                     "         c[id] = a[id] * b[id];\n"
                     "}\n";

cl_program program = clCreateProgramWithSource(context, 1,
                                               &source, NULL, NULL);
clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
cl_kernel kernel = clCreateKernel(program, "dp_mul", NULL);
clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*) &d_buffer);
cISetKernelArg(kernel, 1, sizeof(int), (void*) &N);

// Set number of work-items in a work-group
size_t localWorkSize = 256;
// round up
int numWorkGroups = (N + localWorkSize - 1) / localWorkSize;
// must be evenly divisible by localWorkSize
size_t globalWorkSize = numWorkGroups * localWorkSize;
clEnqueueNDRangeKernel(cmd_queue, kernel, 1, NULL,
                       &globalWorkSize, &localWorkSize, 0, NULL, NULL);