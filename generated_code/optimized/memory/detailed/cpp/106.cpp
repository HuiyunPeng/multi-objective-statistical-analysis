#include <vector>

using namespace std;

vector<int> f(int n) {
    if (n <= 0) return {};

    vector<int> out(n);
    int sum = 0, prod = 1;

    for (int i = 1; i <= n; ++i) {
        sum += i;
        prod *= i;
        out[i - 1] = (i % 2 == 0) ? prod : sum;
    }

    return out;
}
