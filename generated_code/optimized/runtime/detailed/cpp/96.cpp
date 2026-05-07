#include <vector>
#include <cmath>

using namespace std;

vector<int> count_up_to(int n) {
    vector<int> out;
    if (n <= 2) return out;

    if (n < 17) out.reserve(n);
    else out.reserve(static_cast<int>(1.25506 * n / log(static_cast<double>(n))));

    out.push_back(2);
    if (n <= 3) return out;

    const int m = n / 2 - 1; // odd numbers: 3, 5, 7, ..., < n
    vector<char> is_prime(m, 1);
    const int limit = static_cast<int>(sqrt(static_cast<double>(n - 1)));

    for (int i = 0, p = 3; p <= limit; ++i, p += 2) {
        if (is_prime[i]) {
            for (int j = (p * p - 3) >> 1; j < m; j += p) {
                is_prime[j] = 0;
            }
        }
    }

    for (int i = 0, p = 3; i < m; ++i, p += 2) {
        if (is_prime[i]) out.push_back(p);
    }

    return out;
}
