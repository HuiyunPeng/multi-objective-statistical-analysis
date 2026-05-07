#include <vector>
using namespace std;

vector<int> f(int n) {
    vector<int> out;
    if (n <= 0) return out;

    out.resize(n);
    int sum = 0, prod = 1;

    for (int i = 1; i <= n; ++i) {
        sum += i;
        prod *= i;
        out[i - 1] = (i & 1) ? sum : prod;
    }

    return out;
}
