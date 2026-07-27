#include <CL/cl.h>
cl_device_id create_device();

int main(int, char **) {
    if (!ocl_init())
        throw;
    static const int res_w = 1200;
    static const int res_h = 640;

	auto device = create_device();
	cl_int err;
	auto context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

    return 0;
}

cl_device_id create_device(){
	cl_platform_id platform;
	cl_device_id dev;
	cl_int err = 0;
	err |= clGetPlatformIDs(1, &platform, NULL);
	err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU,1, &dev, NULL);
	if (err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
	}
	if (err) throw;
	return dev;
}
