#include <vector>
using namespace std;

vector<int> count_up_to(int n) {
    if (n <= 2) return {};

    vector<int> primes;
    primes.push_back(2);

    const int size = n >> 1; // indices map to odd numbers: num = 2*i + 1
    vector<char> composite(size, 0);

    for (int i = 1; (2LL * i + 1) * (2LL * i + 1) < n; ++i) {
        if (!composite[i]) {
            const int p = 2 * i + 1;
            for (long long j = (1LL * p * p) >> 1; j < size; j += p) {
                composite[(int)j] = 1;
            }
        }
    }

    for (int i = 1; i < size; ++i) {
        if (!composite[i]) primes.push_back(2 * i + 1);
    }

    return primes;
}
