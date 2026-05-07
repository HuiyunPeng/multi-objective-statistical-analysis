#include <vector>
using namespace std;

int add_elements(vector<int> arr, int k) {
    if (k <= 0 || arr.empty()) return 0;

    int n = k < static_cast<int>(arr.size()) ? k : static_cast<int>(arr.size());
    int sum = 0;

    const int* it = arr.data();
    const int* end = it + n;

    while (it != end) {
        int x = *it++;
        if (x >= -99 && x <= 99) {
            sum += x;
        }
    }

    return sum;
}
