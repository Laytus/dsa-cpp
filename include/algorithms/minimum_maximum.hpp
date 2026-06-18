#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <utility>

namespace dsa::algorithms {

template <typename T>
T minimum(
    const std::vector<T>& values
) {
    const std::size_t n = values.size();

    if (n == 0) {
        throw std::invalid_argument("Values must contain at least one element");
    }
    
    T min = values[0];

    for (std::size_t i = 1; i < n; ++i) {
        if (values[i] < min) {
            min = values[i];
        }
    }

    return min;
}

template <typename T>
T maximum(
    const std::vector<T>& values
) {
    const std::size_t n = values.size();

    if (n == 0) {
        throw std::invalid_argument("Values must contain at least one element");
    }
    
    T max = values[0];

    for (std::size_t i = 1; i < n; ++i) {
        if (values[i] > max) {
            max = values[i];
        }
    }

    return max;
}

template <typename T>
std::pair<T, T> minimum_maximum(
    std::vector<T>& values
) {
    const std::size_t n = values.size();

    if (n == 0) {
        throw std::invalid_argument("Values must contain at least one element");
    }
    
    T min;
    T max;
    std::size_t i;

    if (n % 2 == 0) {
        if (values[0] < values[1]) {
            min = values[0];
            max = values[1];
        } else {
            min = values[1];
            max = values[0];
        }
        
        i = 2;
    } else {
        min = values[0];
        max = values[0];
        i = 1;
    }

    for (; i + 1 < n; i += 2) {
        if (values[i] < values[i + 1]) {
            if (values[i] < min) {
                min = values[i];
            }

            if (values[i + 1] > max) {
                max = values[i + 1];
            }
        } else {
            if (values[i] > max) {
                max = values[i];
            }

            if (values[i + 1] < min) {
                min = values[i + 1];
            }
        }
    }

    return {min, max};
}

}  // namespace dsa::algorithms