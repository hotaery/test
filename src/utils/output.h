#ifndef UTILS_OUTPUT_H
#define UTILS_OUTPUT_H

#include <vector>
#include <iostream>

namespace utils {

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    bool first = true;
    os << '[';
    for (auto& elem : vec) {
        if (!first) {
            os << ',';
        } else {
            first = false;
        }
        os << elem;
    }
    os << ']';
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& vec) {
    bool first = true;
    for (auto& v : vec) {
        if (!first) {
            os << '\n';
        } else {
            first = false;
        }
        os << v;
    }
    return os;
}

} // namespace utils 

#endif // UTILS_OUTPUT_H