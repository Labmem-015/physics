decltype(auto) parse_args(int argc, const char *argv[]) {
    std::vector mat_sizes{5, 5, 5};
    constexpr std::string_view error_msg = "Arg {} is not a string!";
    constexpr int max_arg_num = 3;
    for (int pos = 1; pos <= max_arg_num; ++pos) {
        if (argc > pos) {
            if (ph::is_number(argv[pos])) {
                mat_sizes.at(pos - 1) = std::stoi(argv[pos]);
            } else {
                throw std::runtime_error{std::format(error_msg, pos)};
            }
        } else {
            break;
        }
    }
    if (argc - 1 > max_arg_num) {
        std::println("Ignore other arguments except the first {} args", max_arg_num);
    }

	std::print("Sizes are: ");
	for (const auto& s : mat_sizes) {
		std::print("{} ", s);
	}
	std::println("");

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
