#ifndef UTILS_EQUAL_H
#define UTILS_EQIAL_H

#include <vector>

namespace utils {

template <typename T>
bool operator==(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    return !(rhs == lhs);
}

template <typename T>
bool operator==(const std::vector<std::vector<T>>& lhs, const std::vector<std::vector<T>>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t j = 0; j < rhs.size(); ++j) {
            if (lhs[i] != rhs[j]) {
                return false;
            }
        }
    }
    return true;
}

} // namespace utils

#endif 