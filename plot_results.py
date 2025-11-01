#!/usr/bin/env python3
import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

fn = "results.csv" if len(sys.argv) < 2 else sys.argv[1]
df = pd.read_csv(fn)

# pivot
pivot = df.pivot(index='size', columns='algorithm', values='time_ms')

plt.figure(figsize=(8,6))
for col in pivot.columns:
    plt.plot(pivot.index, pivot[col], marker='o', label=col)

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Input size (n)')
plt.ylabel('Time (ms)')
plt.title('Sorting Algorithm Benchmark (log-log)')
plt.grid(True, which='both', ls='--', alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig('runtime_comparison.png', dpi=200)
plt.show()
