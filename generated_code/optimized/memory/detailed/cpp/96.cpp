#include <vector>
using std::vector;

vector<int> count_up_to(int n) {
    if (n <= 2) {
        return {};
    }

    int prime_count = 1; // 2 is prime
    for (int i = 3; i < n; i += 2) {
        bool is_prime = true;
        for (int d = 3; d <= i / d; d += 2) {
            if (i % d == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            ++prime_count;
        }
    }

    vector<int> out;
    out.reserve(prime_count);
    out.push_back(2);

    for (int i = 3; i < n; i += 2) {
        bool is_prime = true;
        for (vector<int>::size_type j = 1; j < out.size(); ++j) {
            int p = out[j];
            if (p > i / p) {
                break;
            }
            if (i % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            out.push_back(i);
        }
    }

    return out;
}
