int main(int, char**) {
    // 1. Set up Platform and Device entries
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, nullptr);

    cl_device_id device;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, nullptr);

    // 2. Build the Compute Context and Command Queue
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, nullptr);
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, nullptr, nullptr);

    // 3. Import and read the GPU kernel code file
    std::ifstream sourceFile("hello_world.cl");
    std::stringstream sourceBuffer;
    sourceBuffer << sourceFile.rdbuf();
    std::string sourceCode = sourceBuffer.str();
    const char *sourcePtr = sourceCode.c_str();
    size_t sourceSize = sourceCode.length();

    // 4. Create and compile the program binary
    cl_program program = clCreateProgramWithSource(context, 1, &sourcePtr, &sourceSize, nullptr);
    clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    cl_kernel kernel = clCreateKernel(program, "hello_kernel", nullptr);

    // 5. Build memory buffer and assign properties
    const int stringLength = 14; // "Hello, World!" with null-terminator
    cl_mem memBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, stringLength * sizeof(char), nullptr, nullptr);

    // 6. Link the memory allocations to kernel parameters
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &memBuffer);

    // 7. Enqueue execution tasks
    size_t globalSize = stringLength;
    clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &globalSize, nullptr, 0, nullptr, nullptr);

    // 8. Extract execution output data back to host CPU memory
    char outputString[stringLength];
    clEnqueueReadBuffer(queue, memBuffer, CL_TRUE, 0, stringLength * sizeof(char), outputString, 0, nullptr, nullptr);

    // Display string output
    std::cout << "Output: " << outputString << std::endl;

    // 9. Free up allocated system memory space
    clReleaseMemObject(memBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}