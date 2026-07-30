int compute_iters(const double x0, const double y0, int iterations) {
	int n = 0;

	// Compute Zn+1 = Zn^2 + c
	// We want to colorize all 'c' that makes this sequence finite. All 'c' that makes |Zn| <= R
	// We approximate our calculations, so we limit them to 'iterations' var.
	// Then evaluate equation, how many iterations it is the part of Mandelbrot set
	for (double x = x0, y = y0; (x * x + y * y <= 2 * 2) && n < iterations; ++n) {
		double xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
	}
	return n;
}

uint to_color_gray(int total_iters, double max_iters) {
	double min_iters = max_iters - 50;
	int pos = 0xff * max(0.f, total_iters - min_iters) / (max_iters - min_iters);
	return 0xff | (pos << 8) | (pos << 16) | (pos << 24); // fill pos in all rgb channels to create a gray gradient (alpha channel is 0xff)
}

// let vars 'px' and 'py' be points of mandelbrot set in the screen center (coords of the center).
// let 'mag' be the scale of zooming into fractal.
// max_iters (drawing accuracy)
// w, h are the sizes of image
// __global uint* result - global output buffer
// result_step - shifting between image lines. 
//
// all those params will be set in host code

__kernel void draw_mandelbrot(double px, double py, double mag, double max_iters,
									int w, int h,
									__global uint * result, int result_step) {
	// work item position
	int ix = get_global_id(0);
	int iy = get_global_id(1);
	
	// Number of work items can be larger than image size due to
	// multiplicity of work group size. So we work strictly within image sizes
	if (ix < w && iy < h) {
		// Get actual pixel for current work item
		double x = px + mag * (double)(ix - w/2) / w;
		double y = py + mag * (double)(iy - h/2) / w;

		int total_iters = compute_iters(x, y, (int)max_iters);
		result[iy * result_step + ix] = to_color_gray(total_iters, max_iters);
	}
}
