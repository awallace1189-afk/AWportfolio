#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
using namespace std;

// Best-Fit Decreasing greedy heuristic for assigning files to disks.
// Inputs:
//  - sizes: vector of file sizes (MB)
//  - caps: vector of disk capacities (MB)
// Output:
//  - map where map[i] is disk index (0-based) assigned to file i, or -1 if not placed
vector<int> bestFitDecreasing(const vector<int>& sizes, const vector<int>& caps) {
    int n = (int)sizes.size();
    int m = (int)caps.size();

    // Pair sizes with original indices and sort descending
    vector<pair<int,int>> files;
    files.reserve(n);
    for (int i = 0; i < n; ++i) files.emplace_back(sizes[i], i);
    sort(files.begin(), files.end(), greater<>());

    vector<int> remaining = caps;       // copy capacities so we can mutate
    vector<int> map(n, -1);
    vector<char> used(m, 0);

    for (auto &p : files) {
        int size = p.first;
        int orig = p.second;

        int best = -1;
        int bestLeftover = INT_MAX;

        for (int j = 0; j < m; ++j) {
            if (remaining[j] < size) continue;
            int leftover = remaining[j] - size;
            if (leftover < bestLeftover) {
                bestLeftover = leftover;
                best = j;
            } else if (leftover == bestLeftover) {
                // tie-breaker: prefer already-used disk to reduce number of used disks
                if (best == -1 || (used[j] && !used[best])) {
                    best = j;
                }
            }
        }

        if (best != -1) {
            map[orig] = best;
            remaining[best] -= size;
            used[best] = 1;
        } else {
            map[orig] = -1; // cannot place this file
        }
    }

    return map;
}

int main() {
    // Example data: file sizes and disk capacities (MB)
    vector<int> sizes = {700, 1200, 300, 1500, 200, 900, 400};
    vector<int> caps  = {1600, 800, 2000, 1000};

    // Single run to show assignment
    auto map = bestFitDecreasing(sizes, caps);

    cout << "Assignment (file_index -> disk_index or -1):\n";
    for (size_t i = 0; i < map.size(); ++i) cout << i << " -> " << map[i] << '\n';

    // Compute stats: remaining per disk and number of used disks
    vector<int> remaining = caps;
    for (size_t i = 0; i < map.size(); ++i) {
        if (map[i] >= 0) remaining[map[i]] -= sizes[i];
    }
    int usedCount = 0; long long unusedOnUsed = 0;
    for (size_t j = 0; j < remaining.size(); ++j) {
        if (remaining[j] < caps[j]) { // some used
            ++usedCount;
            unusedOnUsed += remaining[j];
        }
    }
    cout << "Used disks: " << usedCount << "; Unused storage on used disks: " << unusedOnUsed << " MB\n";

    // Timing: run many iterations and report average time per call
    const int iterations = 50000;
    auto t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        // call with same input; function copies caps internally so safe
        volatile auto tmp = bestFitDecreasing(sizes, caps);
        (void)tmp;
    }
    auto t1 = chrono::high_resolution_clock::now();

    long long ns_total = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    double avg_ns = ns_total / static_cast<double>(iterations);
    double avg_us = avg_ns / 1e3;
    double avg_ms = avg_ns / 1e6;
    double total_s = ns_total / 1e9;

    cout << fixed << setprecision(3);
    cout << "Timing (" << iterations << " runs): total " << total_s << " s; average: "
         << avg_ns << " ns (" << avg_us << " µs, " << avg_ms << " ms) per call\n";

    return 0;
}
