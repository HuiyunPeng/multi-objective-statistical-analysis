#include <vector>
#include <algorithm>

using namespace std;

vector<int> get_odd_collatz(int n) {
    int m = n;
    size_t count = 1;

    while (m != 1) {
        if (m & 1) {
            ++count;
            m = m * 3 + 1;
        } else {
            m >>= 1;
        }
    }

    vector<int> out;
    out.reserve(count);
    out.push_back(1);

    while (n != 1) {
        if (n & 1) {
            out.push_back(n);
            n = n * 3 + 1;
        } else {
            n >>= 1;
        }
    }

    sort(out.begin(), out.end());
    return out;
}
