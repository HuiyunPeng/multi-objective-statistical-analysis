#include <vector>
using namespace std;

vector<int> factorize(int n) {
    vector<int> out;
    out.reserve(32);

    for (int i = 2; i <= n / i; ++i) {
        while (n % i == 0) {
            out.push_back(i);
            n /= i;
        }
    }

    out.push_back(n);
    return out;
}
