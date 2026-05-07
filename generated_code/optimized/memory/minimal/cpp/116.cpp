#include <vector>
#include <algorithm>
using namespace std;

static inline int bitcount_abs(int x) {
    unsigned int n = x < 0 ? static_cast<unsigned int>(-(long long)x)
                           : static_cast<unsigned int>(x);
    int c = 0;
    while (n) {
        c += n & 1u;
        n >>= 1;
    }
    return c;
}

vector<int> sort_array(vector<int> arr) {
    sort(arr.begin(), arr.end(), [](int a, int b) {
        int ca = bitcount_abs(a);
        int cb = bitcount_abs(b);
        if (ca != cb) return ca < cb;
        return a < b;
    });
    return arr;
}
