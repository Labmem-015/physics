#include "utils.hpp"

namespace ph {

std::mt19937_64 gen(std::random_device{}());
std::uniform_int_distribution<int> dist;
std::uniform_real_distribution<float> real_dist;

void seed(int s) {
    gen.seed(s);
    dist.reset();
}

int rand_int(int a, int b) {
    static int _a = dist.param().a();
    static int _b = dist.param().b();
    if (a != _a || b != _b) {
        using param_t = decltype(dist)::param_type;
        dist.param(param_t{a, b});
        _a = a;
        _b = b;
    }
    return dist(gen);
}

float rand_float(float a, float b) {
    static int _a = real_dist.param().a();
    static int _b = real_dist.param().b();
    if (a != _a || b != _b) {
        using param_t = decltype(real_dist)::param_type;
        real_dist.param(param_t{a, b});
        _a = a;
        _b = b;
    }
    return real_dist(gen);
}

bool is_number(std::string_view str) {
    if (str.empty()) {
        return false;
    }
    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

cl::Program compile_kernel(const std::filesystem::path &path, cl::Context &context, cl::Device &dev) {
    std::ifstream cl_file(path);
    if (!cl_file.is_open()) {
        throw std::runtime_error(std::format("Failed to open specified OpenCL kernel file: {}", path.string()));
    }
    std::stringstream buffer;
    buffer << cl_file.rdbuf();
    auto str_view = buffer.view();

    cl::Program::Sources sources;
    sources.push_back({str_view.data(), str_view.size()});
    cl::Program program(context, sources);

    program.build({dev});
    cl_file.close();

    auto binary = program.getInfo<CL_PROGRAM_BINARIES>().at(0);

    if (!binary.empty()) {
        auto out_name = path.stem() / ".cl_compiled";
        std::ofstream out_file(out_name, std::ios::binary);
        if (!cl_file.is_open()) {
            std::println("Can't save compile OpenCL kernel code to the file. {}", out_name.string());
        } else {
            out_file.write(reinterpret_cast<const char *>(binary.data()), binary.size());
            std::println("Successfully saved compiled OpenCL kernel code!");
        }
    }

    return program;
}

} // namespace ph
