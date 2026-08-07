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

} // namespace ph
