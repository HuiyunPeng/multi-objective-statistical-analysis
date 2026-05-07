#include <vector>

std::vector<int> factorize(int n) {
    std::vector<int> out;

    if (n <= 1) {
        out.push_back(n);
        return out;
    }

    while ((n & 1) == 0) {
        out.push_back(2);
        n >>= 1;
    }

    for (int d = 3; d <= n / d; d += 2) {
        while (n % d == 0) {
            out.push_back(d);
            n /= d;
        }
    }

    if (n > 1) {
        out.push_back(n);
    }

    return out;
}
