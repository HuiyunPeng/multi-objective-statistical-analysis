#include <vector>
using namespace std;

int add_elements(vector<int> arr, int k) {
    int sum = 0;
    const int limit = k < static_cast<int>(arr.size()) ? k : static_cast<int>(arr.size());
    for (int i = 0; i < limit; ++i) {
        const int value = arr[i];
        if (value >= -99 && value <= 99) {
            sum += value;
        }
    }
    return sum;
}
