#include <vector>

bool move_one_ball(std::vector<int> arr) {
    const size_t n = arr.size();
    if (n < 2) return true;

    bool seen_drop = false;
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            if (seen_drop) return false;
            seen_drop = true;
        }
    }

    return !seen_drop || arr[n - 1] <= arr[0];
}
