#include <vector>
using namespace std;

bool is_sorted(vector<int> lst) {
    const size_t n = lst.size();
    if (n < 2) return true;

    const int* data = lst.data();
    int prev = data[0];
    int equal_count = 1;

    for (size_t i = 1; i < n; ++i) {
        const int curr = data[i];

        if (curr < prev) return false;

        if (curr == prev) {
            if (++equal_count >= 3) return false;
        } else {
            equal_count = 1;
            prev = curr;
        }
    }

    return true;
}
