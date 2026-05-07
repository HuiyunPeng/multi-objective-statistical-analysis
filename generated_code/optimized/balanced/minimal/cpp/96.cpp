#include <vector>
#include <cmath>
using namespace std;

vector<int> count_up_to(int n) {
    vector<int> primes;
    if (n <= 2) return primes;

    if (n > 10) {
        primes.reserve(static_cast<size_t>(1.25506 * n / std::log(static_cast<double>(n))));
    }

    primes.push_back(2);
    if (n <= 3) return primes;

    const int m = (n - 2) / 2; // Represents odd numbers: 3, 5, 7, ..., < n
    vector<bool> composite(m, false);

    const int limit = static_cast<int>(std::sqrt(static_cast<double>(n - 1)));
    for (int i = 0; 2 * i + 3 <= limit; ++i) {
        if (!composite[i]) {
            const int p = 2 * i + 3;
            const int start = (p * p - 3) / 2;
            for (int j = start; j < m; j += p) {
                composite[j] = true;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        if (!composite[i]) primes.push_back(2 * i + 3);
    }

    return primes;
}
