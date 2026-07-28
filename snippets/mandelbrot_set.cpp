#include "mandelbrot_set_render.hpp"

cl_device_id create_device();

cl_program build_kernel_code(cl_context ctx, cl_device_id dev);

int align(int x, int y);

void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem buff, cl_uint* result, float x, float y, float mag, int w, int h, float iters);

int main(int, char **) {
    static const int res_w = 1200;
    static const int res_h = 640;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(res_w, res_h, "Mandelbrot_set");
	SetTargetFPS(60);

	auto device = create_device();
	cl_int err;
	auto context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
    if (err) throw;
	auto program = build_kernel_code(context, device);
	auto kernel = clCreateKernel(program, "draw_mandelbrot", &err);
	if (err) throw;
	auto command_queue = clCreateCommandQueue(context, device, 0, &err);
	if (err) throw;
	auto cl_mem_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_uint) * res_w * res_h, nullptr, &err);
	if (err) throw;

	std::vector<cl_uint> pixels(res_w * res_h);
	invoke_kernel(kernel, command_queue, cl_mem_buff, pixels.data(), -.5f, 0.f,  4.5f, res_w, res_h, 50);

	clReleaseKernel(kernel);
	clReleaseMemObject(cl_mem_buff);
	clReleaseCommandQueue(command_queue);
	clReleaseProgram(program);
	clReleaseContext(context);

	render_loop(pixels, res_w, res_h);

	CloseWindow();
    return 0;
}

cl_device_id create_device(){
	cl_platform_id platform;
	cl_device_id dev;
	cl_int err = 0;
	err |= clGetPlatformIDs(1, &platform, nullptr);
	err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU,1, &dev, nullptr);
	if (err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, nullptr);
	}
	if (err) throw;
	return dev;
}

cl_program build_kernel_code(cl_context ctx, cl_device_id dev) {
	cl_int err =0;

	std::ifstream cl_file("mandelbrot_set.cl");
	std::stringstream buffer;
	buffer << cl_file.rdbuf();
	const char* source_code = buffer.view().data();
	size_t source_code_size = buffer.view().size();
	auto program = clCreateProgramWithSource(ctx, 1, &source_code, &source_code_size, &err);
	err |= clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
	if (err) throw;
	return program;
}

void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem buff, cl_uint* result, float x, float y, float mag, int w, int h, float iters) { 
	cl_int err = 0;
	err |= clSetKernelArg(kernel, 0, sizeof(float), &x);
	err |= clSetKernelArg(kernel, 1, sizeof(float), &y);
	err |= clSetKernelArg(kernel, 2, sizeof(float), &mag);
	err |= clSetKernelArg(kernel, 3, sizeof(float), &iters);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_int), &w);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_int), &h);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &buff);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_int), &w);
	
	// workgroup sizes: 256x1
	size_t local_size[2] = {256, 1};
	size_t global_size[2] = {
		(size_t)align(w, (int)local_size[0]),
		(size_t)align(h, (int)local_size[1]),
	};

	// run code
	err |= clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, global_size, local_size, 0, nullptr, nullptr);

	// read result
	err |= clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(cl_uint) * w * h, result, 0, nullptr, nullptr);
	clFinish(queue);
}

int align(int x, int y) {
	// we use this formula to align x to y
	return (x + y - 1) / y * y;
}

