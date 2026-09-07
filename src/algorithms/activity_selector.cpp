#include "algorithms/activity_selector.hpp"

#include <stdexcept>
#include <limits>

namespace dsa::algorithms {

namespace  {

void collect_selected_activities(
    const std::vector<std::vector<std::size_t>>& selected,
    const std::vector<int>& padded_s,
    const std::vector<int>& padded_f,
    std::size_t i,
    std::size_t j,
    std::vector<Activity>& activities
) {
    const std::size_t k = selected[i][j];

    if (k == 0) {
        return;
    }

    collect_selected_activities(selected, padded_s, padded_f, i, k, activities);
    activities.push_back(Activity{padded_s[k], padded_f[k]});
    collect_selected_activities(selected, padded_s, padded_f, k, j, activities);
}

}  // namespace

std::vector<Activity> recursive_activity_selector(
    const std::vector<int>& s,
    const std::vector<int>& f,
    std::size_t k
) {
    if (s.size() != f.size()) {
        throw std::invalid_argument("s and f must have the same size");
    }
    
    if (s.empty()) {
        return {};
    }

    const std::size_t n = s.size();

    if (k >= n) {
        throw std::out_of_range("k must be a valid padded index");
    }

    std::size_t m = k + 1;
    
    while (m < n && s[m] < f[k]) {
        ++m;
    }
    
    if (m < n) {
        std::vector<Activity> activities {Activity{s[m], f[m]}};

        auto remaining = recursive_activity_selector(s, f, m);
        activities.insert(
            activities.end(),
            remaining.begin(),
            remaining.end()
        );

        return activities;
    }
    
    return {};
}

std::vector<Activity> dynamic_activity_selector(
    const std::vector<int>& s,
    const std::vector<int>& f
) {
    if (s.size() != f.size()) {
        throw std::invalid_argument("s and f must have the same size");
    }
    
    if (s.empty()) {
        return {};
    }

    const std::size_t n = s.size();

    std::vector<int> padded_s(n + 2, 0);
    std::vector<int> padded_f(n + 2, 0);

    for (std::size_t i = 0; i < n; ++i) {
        padded_s[i + 1] = s[i];
        padded_f[i + 1] = f[i];
    }

    padded_s[n + 1] = std::numeric_limits<int>::max();
    padded_f[n + 1] = std::numeric_limits<int>::max();

    std::vector<std::vector<std::size_t>> c(
        n + 2,
        std::vector<std::size_t>(n + 2, 0)
    );

    std::vector<std::vector<std::size_t>> selected(
        n + 2,
        std::vector<std::size_t>(n + 2, 0)
    );

    for (std::size_t length = 2; length <= n + 1; ++length) {
        for (std::size_t i = 0; i + length <= n + 1; ++i) {
            const std::size_t j = i + length;

            for (std::size_t k = i + 1; k < j; ++k) {
                if (padded_f[i] <= padded_s[k] && padded_f[k] <= padded_s[j]) {
                    const std::size_t candidate = c[i][k] + c[k][j] + 1;

                    if (candidate > c[i][j]) {
                        c[i][j] = candidate;
                        selected[i][j] = k;
                    }
                }
            }
        }
    }

    std::vector<Activity> activities;
    collect_selected_activities(selected, padded_s, padded_f, 0, n + 1, activities);

    return activities;
}

std::vector<Activity> greedy_activity_selector(
    const std::vector<int>& s,
    const std::vector<int>& f
) {
    if (s.size() != f.size()) {
        throw std::invalid_argument("s and f must have the same size");
    }
    
    if (s.empty()) {
        return {};
    }

    const std::size_t n = s.size();

    std::vector<Activity> activities{Activity{s[0], f[0]}};

    std::size_t k = 0;

    for (std::size_t m = 1; m < n; ++m) {
        if (s[m] >= f[k]) {
            Activity new_a{s[m], f[m]};
            activities.push_back(new_a);
            k = m;
        }
    }

    return activities;
}

}  // namespace dsa::algorithms