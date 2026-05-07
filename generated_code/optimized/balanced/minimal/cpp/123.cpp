#include <vector>
#include <algorithm>

std::vector<int> get_odd_collatz(int n) {
    std::vector<int> out;
    out.reserve(32);
    out.push_back(1);

    if (n > 1) {
        long long x = n;
        while (x != 1) {
            if (x & 1LL) {
                out.push_back(static_cast<int>(x));
                x = x * 3 + 1;
            }
            x >>= __builtin_ctzll(static_cast<unsigned long long>(x));
        }
    } else {
        while (n != 1) {
            if (n % 2 == 1) {
                out.push_back(n);
                n = n * 3 + 1;
            } else {
                n /= 2;
            }
        }
    }

    if (out.size() > 1) {
        std::sort(out.begin(), out.end());
    }
    return out;
}
