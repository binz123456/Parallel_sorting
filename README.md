# Parallel Sorting Benchmark (Quicksort & Mergesort) — OpenMP

## Overview
Small benchmark that implements **quicksort** and **mergesort** in C++, with both **serial** and **OpenMP-parallel** versions. The program measures execution time for several input sizes and writes results to `results.csv`. A Python script plots runtime vs input size.

## Features
- Serial Quicksort & Mergesort
- Parallel Quicksort & Mergesort (OpenMP tasks)
- Simple thresholding to avoid oversubscription
- CSV output and Python plotting (log-log scale)

## Requirements
- C++17 compiler (g++)
- CMake
- OpenMP enabled compiler
- Python3 with `pandas` and `matplotlib`:
  ```bash
  pip install pandas matplotlib
