enum class Mode {
    CPU,
    GPU,
    _count,
} mode = Mode::GPU;

decltype(auto) parse_args(int argc, const char *argv[]) {
    std::vector mat_sizes{5, 5, 5};
    constexpr std::string_view error_msg = "Unknown arg '{}' at pos {}!";
    constexpr int mat_max_args = 3;
    bool are_sizes_sequential = true;
    for (int pos = 1; pos < argc; ++pos) {
        std::string_view arg = argv[pos];
        if (pos <= mat_max_args && are_sizes_sequential && ph::is_number(arg)) {
            mat_sizes.at(pos - 1) = std::stoi(std::string(arg));
        } else if (arg == "-h" || arg == "--help") {
            std::println("Awailable args: ([dim1] [dim2] [dim3]) [--cpu] [--gpu] [--help] [-h]");
            std::exit(0);
        } else if (arg == "--cpu") {
            if (pos <= mat_max_args) {
                are_sizes_sequential = false;
            }
            mode = Mode::CPU;
        } else if (arg == "--gpu") {
            if (pos <= mat_max_args) {
                are_sizes_sequential = false;
            }
            mode = Mode::GPU;
        } else {
            throw std::runtime_error{std::format(error_msg, argv[pos], pos)};
        }
    }

    std::print("Sizes are: ");
    for (const auto &s : mat_sizes) {
        std::print("{} ", s);
    }
    std::println("");

    return mat_sizes;
}

cl::Device get_deivce(cl::Context &context) {
    if (mode == Mode::GPU) {
        context = cl::Context(CL_DEVICE_TYPE_GPU);
    } else {
        context = cl::Context(CL_DEVICE_TYPE_CPU);
    }

    auto *err = new cl_int{0};
    auto dev_list = context.getInfo<CL_CONTEXT_DEVICES>(err);
    if (*err != CL_SUCCESS || dev_list.empty()) {
        throw std::runtime_error("No awailable compute device");
    }
    auto dev = dev_list.front();
    auto dev_name = dev.getInfo<CL_DEVICE_NAME>(err);
    if (*err != CL_SUCCESS) {
        throw std::runtime_error("Couldn't get device name");
    }
    auto dev_vendor = dev.getInfo<CL_DEVICE_VENDOR>(err);
    if (*err != CL_SUCCESS) {
        throw std::runtime_error("Couldn't get device's vendor");
    }

    std::println("Device name: {}", dev_name);
    std::println("Device's vendor: {}", dev_vendor);

    return dev;
}

void init(std::vector<float> &mat) {
    for (auto &el : mat) {
        el = ph::rand_int(0, 10);
    }
}

void print(const std::vector<float> &mat, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::print("{} ", mat[i * rows + j]);
        }
        std::println("");
    }
}

int main(int argc, const char *argv[]) {
    try {
        auto mat_sizes = parse_args(argc, argv);

        cl::Context context;

        auto dev = get_deivce(context);

        std::vector<float> mat1(mat_sizes.at(0) * mat_sizes.at(1));
        std::vector<float> mat2(mat_sizes.at(1) * mat_sizes.at(2));
        std::vector<float> result(mat_sizes.at(0) * mat_sizes.at(2));

        init(mat1);
        init(mat2);

        std::println("\nVec1:");
        print(mat1, mat_sizes.at(0), mat_sizes.at(1));
        std::println("\nVec2:");
        print(mat2, mat_sizes.at(1), mat_sizes.at(2));

        for (int row_a = 0; row_a < mat_sizes.at(0); ++row_a) {
            for (int col_b = 0; col_b < mat_sizes.at(2); ++col_b) {
                float sum = 0;
                for (int el = 0; el < mat_sizes.at(1); ++el) {
                    auto index1 = el + row_a * mat_sizes.at(0);
                    auto index2 = col_b + el * mat_sizes.at(1);
                    sum += mat1[index1] * mat2[index2];
                }
                auto index = row_a * mat_sizes.at(0) + col_b;
                result[index] = sum;
            }
        }

        std::println("\nProduct:");
        print(result, mat_sizes.at(0), mat_sizes.at(2));

    } catch (const std::exception &e) {
        std::println("{}", e.what());
        return -1;
    }
    return 0;
}
