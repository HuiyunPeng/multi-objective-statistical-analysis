#include <vector>
using namespace std;

vector<int> f(int n) {
    vector<int> out;
    if (n <= 0) return out;

    out.reserve(n);

    int sum = 0, prod = 1;
    int i = 1;

    for (; i + 1 <= n; i += 2) {
        sum += i;
        prod *= i;
        out.push_back(sum);

        sum += i + 1;
        prod *= i + 1;
        out.push_back(prod);
    }

    if (i <= n) {
        sum += i;
        prod *= i;
        out.push_back(sum);
    }

    return out;
}
