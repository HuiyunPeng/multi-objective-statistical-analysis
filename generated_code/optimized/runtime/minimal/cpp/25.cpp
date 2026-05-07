#include <vector>
using namespace std;

vector<int> factorize(int n) {
    if (n <= 1) return {n};

    vector<int> out;
    while ((n & 1) == 0) {
        out.push_back(2);
        n >>= 1;
    }

    for (int i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            out.push_back(i);
            n /= i;
        }
    }

    out.push_back(n);
    return out;
}
