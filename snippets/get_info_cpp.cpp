template <typename T> using pair = std::pair<T, std::string>;

int main(int, const char **) {
    auto *err = new cl_int{0};

    std::vector<cl::Platform> platforms;
    *err = cl::Platform::get(&platforms);
	std::println("Found {} platforms", platforms.size());
    if (*err != CL_SUCCESS) {
        std::println("Couldn't retrieve platforms");
        return -1;
    }

    for (auto &platform : platforms) {
		std::println("==========");
        auto platform_name = platform.getInfo<CL_PLATFORM_NAME>(err);
        auto platform_vendor = platform.getInfo<CL_PLATFORM_VENDOR>(err);
        std::println("Platform name: {}", platform_name);
        std::println("Platform vendor: {}\n", platform_vendor);

        std::vector<cl::Device> gpu_devices;
        std::vector<cl::Device> cpu_devices;
        platform.getDevices(CL_DEVICE_TYPE_GPU, &gpu_devices);
        platform.getDevices(CL_DEVICE_TYPE_CPU, &cpu_devices);

        cl::Context context(CL_DEVICE_TYPE_ALL);
        auto context_devices = context.getInfo<CL_CONTEXT_DEVICES>(err);

        pair cpu{cpu_devices, "cpu"};
        pair gpu{gpu_devices, "gpu"};
        pair ctx{context_devices, "ctx"};

        std::apply(
            [&err](const auto &...tuple_map) {
                auto f = [&err](const auto &pair_entry) -> void {
                    auto &[dev_list, name] = pair_entry;
                    if (dev_list.empty()) {
                        std::println("Empty {} dev list. Skip\n", name);
                        return;
                    }
                    for (auto &dev : dev_list) {
                        auto device_name = dev.template getInfo<CL_DEVICE_NAME>(err);
                        auto device_vendor = dev.template getInfo<CL_DEVICE_VENDOR>(err);
                        auto device_type = dev.template getInfo<CL_DEVICE_TYPE>(err);
                        auto device_max_cu = dev.template getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>(err);

                        std::println("Source: {}", name);
                        std::println("Device name: {}", device_name);
                        std::println("Device vendor: {}", device_vendor);
                        std::println("Device type: {}", device_type);
                        std::println("Device max compute units: {}\n", device_max_cu);
                    }
                };
                (f(tuple_map), ...);
            },
            std::forward_as_tuple(cpu, gpu, ctx));
    }
    return 0;
}
