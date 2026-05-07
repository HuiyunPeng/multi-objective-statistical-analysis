#include <vector>
using namespace std;

vector<int> f(int n) {
    int sum = 0, prod = 1;
    vector<int> out(n);
    for (int i = 1; i <= n; ++i) {
        sum += i;
        prod *= i;
        out[i - 1] = (i % 2 == 0) ? prod : sum;
    }
    return out;
}
