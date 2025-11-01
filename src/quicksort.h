#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
#include <omp.h>

// Threshold below which we use std::sort (non-recursive base case)
static const int QSORT_PARALLEL_THRESHOLD = 1 << 13; // 8192

inline int partition_std(std::vector<int>& a, int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; ++j) {
        if (a[j] <= pivot) {
            ++i;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i+1], a[r]);
    return i+1;
}

inline void quicksort_serial(std::vector<int>& a, int l, int r) {
    if (l >= r) return;
    if (r - l + 1 <= 32) {
        std::sort(a.begin() + l, a.begin() + r + 1);
        return;
    }
    int p = partition_std(a, l, r);
    quicksort_serial(a, l, p - 1);
    quicksort_serial(a, p + 1, r);
}

// Parallel quicksort using OpenMP tasks
inline void quicksort_parallel_task(std::vector<int>& a, int l, int r, int depth = 0) {
    if (l >= r) return;
    int len = r - l + 1;
    if (len <= QSORT_PARALLEL_THRESHOLD) {
        // small: run serially (std::sort)
        std::sort(a.begin() + l, a.begin() + r + 1);
        return;
    }

    int p = partition_std(a, l, r);

    // create tasks for both sides
    #pragma omp task shared(a) if(len > QSORT_PARALLEL_THRESHOLD)
    quicksort_parallel_task(a, l, p - 1, depth + 1);

    #pragma omp task shared(a) if(len > QSORT_PARALLEL_THRESHOLD)
    quicksort_parallel_task(a, p + 1, r, depth + 1);

    #pragma omp taskwait
}

// wrapper to start parallel region
inline void quicksort_parallel(std::vector<int>& a) {
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            quicksort_parallel_task(a, 0, int(a.size()) - 1);
        }
    }
}

#endif // QUICKSORT_H
