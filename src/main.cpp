#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

#include "utils.h"
#include "quicksort.h"
#include "mergesort.h"

int main() {
    std::vector<size_t> sizes = {100000, 250000, 500000, 1000000}; // adjust as you like
    std::ofstream csv("results.csv");
    csv << "algorithm,size_ms,time_ms\n"; // small bug: we'll write algorithm,size,time; keep header correct
    csv.close(); // rewrite below properly

    std::ofstream out("results.csv");
    out << "algorithm,size,time_ms\n";

    std::cout << "Parallel Sorting Benchmark\n";
    #ifdef _OPENMP
    std::cout << "OpenMP threads = " << omp_get_max_threads() << "\n";
    #else
    std::cout << "OpenMP not enabled\n";
    #endif

    for (size_t n : sizes) {
        std::cout << "\n-- N = " << n << " --\n";
        auto base = make_random_vector(n, 0, 1000000);

        // Serial Quicksort
        auto a = base;
        double t0 = now_ms();
        quicksort_serial(a, 0, int(a.size()) - 1);
        double t1 = now_ms();
        double ms_quick_serial = t1 - t0;
        std::cout << "quicksort_serial: " << ms_quick_serial << " ms, sorted=" << is_sorted_asc(a) << "\n";
        out << "quicksort_serial," << n << "," << std::fixed << std::setprecision(3) << ms_quick_serial << "\n";

        // Parallel Quicksort
        a = base;
        t0 = now_ms();
        quicksort_parallel(a);
        t1 = now_ms();
        double ms_quick_parallel = t1 - t0;
        std::cout << "quicksort_parallel: " << ms_quick_parallel << " ms, sorted=" << is_sorted_asc(a) << "\n";
        out << "quicksort_parallel," << n << "," << std::fixed << std::setprecision(3) << ms_quick_parallel << "\n";

        // Serial Mergesort
        a = base;
        t0 = now_ms();
        mergesort_serial(a);
        t1 = now_ms();
        double ms_merge_serial = t1 - t0;
        std::cout << "mergesort_serial: " << ms_merge_serial << " ms, sorted=" << is_sorted_asc(a) << "\n";
        out << "mergesort_serial," << n << "," << std::fixed << std::setprecision(3) << ms_merge_serial << "\n";

        // Parallel Mergesort
        a = base;
        t0 = now_ms();
        mergesort_parallel(a);
        t1 = now_ms();
        double ms_merge_parallel = t1 - t0;
        std::cout << "mergesort_parallel: " << ms_merge_parallel << " ms, sorted=" << is_sorted_asc(a) << "\n";
        out << "mergesort_parallel," << n << "," << std::fixed << std::setprecision(3) << ms_merge_parallel << "\n";
    }

    out.close();
    std::cout << "\nResults written to results.csv\n";
    std::cout << "Use `python3 plot_results.py results.csv` to plot.\n";
    return 0;
}
