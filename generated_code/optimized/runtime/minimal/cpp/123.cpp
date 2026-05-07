#include <vector>
#include <algorithm>
using namespace std;

vector<int> get_odd_collatz(int n) {
    vector<int> out;
    out.reserve(32);
    out.push_back(1);

    while (n != 1) {
        while (n != 1 && (n % 2 == 0)) {
            n /= 2;
        }
        if (n == 1) break;

        out.push_back(n);
        n = n * 3 + 1;
    }

    sort(out.begin(), out.end());
    return out;
}
