#include <vector>
using namespace std;

vector<int> f(int n) {
    vector<int> out;
    if (n <= 0) return out;

    out.resize(n);
    int sum = 0, prod = 1;
    int i = 1;

    for (; i + 1 <= n; i += 2) {
        sum += i;
        prod *= i;
        out[i - 1] = sum;

        sum += i + 1;
        prod *= i + 1;
        out[i] = prod;
    }

    if (i <= n) {
        sum += i;
        prod *= i;
        out[i - 1] = sum;
    }

    return out;
}
