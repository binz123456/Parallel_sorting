#ifndef MERGESORT_H
#define MERGESORT_H

#include <algorithm>
#include <vector>
#include <omp.h>

// Threshold below which we use std::sort
static const int MSORT_PARALLEL_THRESHOLD = 1 << 14; // 16384

inline void merge_ranges(std::vector<int>& a, std::vector<int>& tmp, int l, int m, int r) {
    int i = l, j = m+1, k = l;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int x = l; x <= r; ++x) a[x] = tmp[x];
}

inline void mergesort_serial_rec(std::vector<int>& a, std::vector<int>& tmp, int l, int r) {
    if (l >= r) return;
    if (r - l + 1 <= 32) {
        std::sort(a.begin() + l, a.begin() + r + 1);
        return;
    }
    int m = (l + r) >> 1;
    mergesort_serial_rec(a, tmp, l, m);
    mergesort_serial_rec(a, tmp, m+1, r);
    merge_ranges(a, tmp, l, m, r);
}

inline void mergesort_serial(std::vector<int>& a) {
    std::vector<int> tmp(a.size());
    mergesort_serial_rec(a, tmp, 0, int(a.size()) - 1);
}

// Parallel mergesort (OpenMP tasks)
inline void mergesort_parallel_rec(std::vector<int>& a, std::vector<int>& tmp, int l, int r) {
    if (l >= r) return;
    int len = r - l + 1;
    if (len <= MSORT_PARALLEL_THRESHOLD) {
        std::sort(a.begin() + l, a.begin() + r + 1);
        return;
    }
    int m = (l + r) >> 1;
    #pragma omp task shared(a, tmp) if(len > MSORT_PARALLEL_THRESHOLD)
    mergesort_parallel_rec(a, tmp, l, m);

    #pragma omp task shared(a, tmp) if(len > MSORT_PARALLEL_THRESHOLD)
    mergesort_parallel_rec(a, tmp, m+1, r);

    #pragma omp taskwait
    merge_ranges(a, tmp, l, m, r);
}

inline void mergesort_parallel(std::vector<int>& a) {
    std::vector<int> tmp(a.size());
    #pragma omp parallel
    {
        #pragma omp single nowait
        mergesort_parallel_rec(a, tmp, 0, int(a.size()) - 1);
    }
}

#endif // MERGESORT_H
