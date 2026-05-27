#include <cstddef>
#include <tuple>
#include <vector>

namespace dsa::algorithms {

std::tuple<std::size_t, std::size_t, int> find_maximum_subarray_brute_force(
    const std::vector<int>& inputs,
    std::size_t low,
    std::size_t high
);

}  // namespace dsa::algorithms