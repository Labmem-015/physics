int main(int, char**) {
	cl_platform_id platform;
    cl_device_id device;
    cl_int err = 0;
    err |= clGetPlatformIDs(1, &platform, nullptr);
    err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr);
    if (err == CL_DEVICE_NOT_FOUND) {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, nullptr);
    }
    if (err)
        throw;
	

	// Allocate memory for the extension string
    size_t ext_size;
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, NULL, &ext_size);
    char *extensions = (char *)malloc(ext_size);

    // Fetch the supported extensions
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, ext_size, extensions, NULL);

    // Check for the double precision string
    if (strstr(extensions, "cl_khr_fp64") != NULL) {
        printf("Double precision is supported!\n");
    } else {
        printf("Double precision is NOT supported.\n");
    }

    free(extensions);
	return 0;
}
