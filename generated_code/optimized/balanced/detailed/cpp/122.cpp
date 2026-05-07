#include <vector>

using namespace std;

int add_elements(vector<int> arr, int k) {
    int sum = 0;
    const int* data = arr.data();

    for (int i = 0; i < k; ++i) {
        const int v = data[i];
        if (v >= -99 && v <= 99) {
            sum += v;
        }
    }

    return sum;
}
