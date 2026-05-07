#include <vector>
using namespace std;

bool below_zero(vector<int> operations) {
    long long balance = 0;
    const int* data = operations.data();
    const size_t n = operations.size();

    for (size_t i = 0; i < n; ++i) {
        balance += data[i];
        if (balance < 0) return true;
    }
    return false;
}
