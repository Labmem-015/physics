#pragma once

namespace ph {

void seed(int s);

int rand_int(int a, int b);
float rand_float(float a, float b);

bool is_number(std::string_view str);

cl::Program compile_kernel(const std::filesystem::path &path, cl::Context &context, cl::Device &dev);

} // namespace ph
