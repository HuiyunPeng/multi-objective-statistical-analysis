#include <vector>
using namespace std;

vector<int> factorize(int n) {
    vector<int> out;
    out.reserve(32);

    if (n <= 1) {
        out.push_back(n);
        return out;
    }

    while ((n & 1) == 0) {
        out.push_back(2);
        n >>= 1;
    }

    while (n % 3 == 0) {
        out.push_back(3);
        n /= 3;
    }

    for (int d = 5; (long long)d * d <= n; d += 6) {
        while (n % d == 0) {
            out.push_back(d);
            n /= d;
        }

        int d2 = d + 2;
        while (n % d2 == 0) {
            out.push_back(d2);
            n /= d2;
        }
    }

    if (n > 1) {
        out.push_back(n);
    }

    return out;
}
