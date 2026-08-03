decltype(auto) parse_args(int argc, const char *argv[]) {
    std::vector mat_sizes{5, 5};
    constexpr std::string_view error_msg = "Arg {} is not a string!";
    auto pos = 1;
    if (argc > pos) {
        if (ph::is_number(argv[pos])) {
            mat_sizes.at(pos) = std::stoi(argv[pos]);
        } else {
            throw std::runtime_error{std::format(error_msg, pos)};
        }
    }
    pos = 2;
    if (argc > pos) {
        if (ph::is_number(argv[pos])) {
            mat_sizes.at(pos) = std::stoi(argv[pos]);
        } else {
            throw std::runtime_error{std::format(error_msg, pos)};
        }
    }
    pos = 3;
    if (argc > pos) {
        std::println("Ignore other arguments except the first two");
    }
    return mat_sizes;
}

int main(int argc, const char *argv[]) {
    auto mat_sizes = parse_args(argc, argv);

    auto* err = new cl_int{0};
    auto platform = cl::Platform::get(err);
    cl::Device dev;
    dev.get();

    auto platform_name = platform.getInfo<CL_PLATFORM_NAME>(err);
    auto platform_vendor = platform.getInfo<CL_PLATFORM_VENDOR>(err);
    auto device_max_cu = dev.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>(err);

    return 0;
}
