#include <vector>
#include <algorithm>
using namespace std;

vector<int> get_odd_collatz(int n) {
    vector<int>::size_type count = 1;
    int m = n;

    while (m != 1) {
        if (m & 1) {
            ++count;
            m = m * 3 + 1;
        } else {
            m /= 2;
        }
    }

    vector<int> out(count);
    out[0] = 1;

    vector<int>::size_type idx = 1;
    while (n != 1) {
        if (n & 1) {
            out[idx++] = n;
            n = n * 3 + 1;
        } else {
            n /= 2;
        }
    }

    sort(out.begin(), out.end());
    return out;
}
