#pragma once

namespace ph {

void seed(int s);

int rand_int(int a, int b);
float rand_float(float a, float b);

bool is_number(std::string_view str);

} // namespace ph
