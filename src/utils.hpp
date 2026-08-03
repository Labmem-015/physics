#pragma once

namespace ph {

inline bool
is_number(std::string_view str) {
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
