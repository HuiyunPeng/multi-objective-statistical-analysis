#include <vector>
using namespace std;

bool below_zero(vector<int> operations) {
    int sum = 0;
    for (size_t i = 0, n = operations.size(); i < n; ++i) {
        sum += operations[i];
        if (sum < 0) return true;
    }
    return false;
}
