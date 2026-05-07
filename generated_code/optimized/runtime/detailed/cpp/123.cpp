#include <vector>
#include <algorithm>
using namespace std;

vector<int> get_odd_collatz(int n) {
    vector<int> out;
    out.reserve(32);
    out.push_back(1);

    while (n != 1) {
        if ((n & 1) == 0) {
            n >>= __builtin_ctz(static_cast<unsigned int>(n));
        } else {
            out.push_back(n);
            n = n * 3 + 1;
            n >>= __builtin_ctz(static_cast<unsigned int>(n));
        }
    }

    sort(out.begin(), out.end());
    return out;
}
