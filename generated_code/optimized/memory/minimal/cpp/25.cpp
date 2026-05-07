#include <vector>
using namespace std;

vector<int> factorize(int n) {
    vector<int> out;
    for (int i = 2; i <= n / i; ++i) {
        while (n % i == 0 && i <= n / i) {
            out.push_back(i);
            n /= i;
        }
    }
    out.push_back(n);
    return out;
}
