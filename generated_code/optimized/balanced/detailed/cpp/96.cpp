#include <vector>
#include <cmath>

std::vector<int> count_up_to(int n) {
    std::vector<int> primes;
    if (n <= 2) return primes;

    primes.push_back(2);
    if (n <= 3) return primes;

    if (n >= 17) {
        const double dn = static_cast<double>(n);
        primes.reserve(static_cast<std::size_t>(dn / (std::log(dn) - 1.1)) + 1);
    } else {
        primes.reserve(n / 2);
    }

    const int sieve_size = n / 2 - 1; // represents odd numbers: 3, 5, 7, ...
    std::vector<bool> composite(sieve_size, false);
    const int limit = static_cast<int>(std::sqrt(static_cast<double>(n - 1)));

    for (int p = 3; p <= limit; p += 2) {
        const int idx = (p - 3) / 2;
        if (!composite[idx]) {
            const int start = (p * p - 3) / 2;
            for (int j = start; j < sieve_size; j += p) {
                composite[j] = true;
            }
        }
    }

    for (int i = 0; i < sieve_size; ++i) {
        if (!composite[i]) {
            primes.push_back((i << 1) + 3);
        }
    }

    return primes;
}
