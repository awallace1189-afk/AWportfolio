#include <iostream>
#include <vector>
using namespace std;

/*
 * reverseArray()
 * ----------------
 * Reverses the order of elements in an integer array in place.
 * This algorithm uses two indices—one starting at the beginning
 * and one at the end—and swaps elements until the indices meet.
 *
 * Because only a constant amount of extra memory is used
 * (temporary variable for swapping), this is an in‑place algorithm.
 */
void reverseArray(vector<int>& arr) {
    int left = 0;                  // Start index
    int right = arr.size() - 1;    // End index

    while (left < right) {
        // Swap elements at left and right
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        // Move indices toward the center
        left++;
        right--;
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};

    reverseArray(arr);

    cout << "Reversed array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}