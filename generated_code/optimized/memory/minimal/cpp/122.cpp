#include <vector>
using std::vector;

int add_elements(vector<int> arr, int k) {
    int sum = 0;
    const int n = static_cast<int>(arr.size());
    if (k > n) k = n;

    for (int i = 0; i < k; ++i) {
        const int v = arr[i];
        if (v >= -99 && v <= 99) {
            sum += v;
        }
    }
    return sum;
}
