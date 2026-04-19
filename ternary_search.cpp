#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

// Ternary search on a sorted vector<string>.
// Returns the index of target if found, otherwise -1.
int ternarySearch(const vector<string>& arr, const string& target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int third = (right - left) / 3;
        int mid1 = left + third;
        int mid2 = right - third;

        if (arr[mid1] == target) return mid1;
        if (arr[mid2] == target) return mid2;

        if (target < arr[mid1]) {
            // Target is in first third
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            // Target is in last third
            left = mid2 + 1;
        } else {
            // Target is in middle third
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }

    return -1;
}

int main() {
    // Playlist must be sorted alphabetically for ternary search to work.
    vector<string> playlist = {
        "A Day in the Life",
        "Bohemian Rhapsody",
        "Hotel California",
        "Imagine",
        "Stairway to Heaven",
        "Sweet Child O' Mine",
        "Wonderwall"
    };

    string target1 = "Imagine";          // existing song
    string target2 = "Nothing Else Matters"; // not in playlist

    // Measure runtime: run the search many times and report average time per search
    const int iterations = 100000;

    cout << "Searching for '" << target1 << "'...\n";
    int idx1 = -1;
    auto t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        idx1 = ternarySearch(playlist, target1);
    }
    auto t1 = chrono::high_resolution_clock::now();
    auto ns_total1 = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    double avg_ns1 = ns_total1 / static_cast<double>(iterations);
    cout << "Result: " << idx1 << (idx1 >= 0 ? " (found)\n" : " (not found)\n");
    cout << "Average time: " << avg_ns1 << " ns/search (" << iterations << " iterations)\n";

    cout << "Searching for '" << target2 << "'...\n";
    int idx2 = -1;
    t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        idx2 = ternarySearch(playlist, target2);
    }
    t1 = chrono::high_resolution_clock::now();
    auto ns_total2 = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    double avg_ns2 = ns_total2 / static_cast<double>(iterations);
    cout << "Result: " << idx2 << (idx2 >= 0 ? " (found)\n" : " (not found)\n");
    cout << "Average time: " << avg_ns2 << " ns/search (" << iterations << " iterations)\n";

    return 0;
}
