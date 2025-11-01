#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <random>
#include <vector>

// high resolution timer helpers
inline double now_ms() {
    using Clock = std::chrono::high_resolution_clock;
    return std::chrono::duration<double, std::milli>(Clock::now().time_since_epoch()).count();
}

inline std::vector<int> make_random_vector(size_t n, int lo = 0, int hi = 100000) {
    std::vector<int> v(n);
    std::mt19937_64 rng(123456789);
    std::uniform_int_distribution<int> dist(lo, hi);
    for (size_t i = 0; i < n; ++i) v[i] = dist(rng);
    return v;
}

inline bool is_sorted_asc(const std::vector<int>& a) {
    for (size_t i = 1; i < a.size(); ++i) if (a[i-1] > a[i]) return false;
    return true;
}

#endif // UTILS_H
