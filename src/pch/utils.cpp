#include "utils.hpp"

namespace ph {

std::mt19937_64 gen(std::random_device{}());
std::uniform_int_distribution<int> dist;

void seed(int s) {
    gen.seed(s);
    dist.reset();
}

int rand(int a, int b) {
    static int _a = a;
    static int _b = b;
    if (a != _a || b != _b) {
        using param_t = decltype(dist)::param_type;
        dist.param(param_t{a, b});
    }
    return dist(gen);
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
