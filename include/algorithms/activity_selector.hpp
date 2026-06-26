#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

struct Activity {
    int start;
    int finish;
};

std::vector<Activity> recursive_activity_selector(
    const std::vector<int>& s,
    const std::vector<int>& f,
    std::size_t k
);

std::vector<Activity> dynamic_activity_selector(
    const std::vector<int>& s,
    const std::vector<int>& f
);

std::vector<Activity> greedy_activity_selector(
    const std::vector<int>& s,
    const std::vector<int>& f
);

}  // namespace dsa::algorithms