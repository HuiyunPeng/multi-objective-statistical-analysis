#include <vector>
using namespace std;

vector<int> f(int n) {
    if (n <= 0) return {};

    vector<int> out;
    out.reserve(n);

    int sum = 0, prod = 1;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
        prod *= i;
        out.push_back(sum);

        if (i == n) break;

        ++i;
        sum += i;
        prod *= i;
        out.push_back(prod);
    }

    return out;
}
