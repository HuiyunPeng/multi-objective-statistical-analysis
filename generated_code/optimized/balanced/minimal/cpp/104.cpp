#include <vector>
#include <algorithm>
using namespace std;

vector<int> unique_digits(vector<int> x) {
    size_t write = 0;

    for (int num : x) {
        if (num < 0) {
            x[write++] = num;
            continue;
        }
        if (num == 0) continue;

        int n = num;
        while (n > 0 && (n & 1)) {
            n /= 10;
        }

        if (n == 0) {
            x[write++] = num;
        }
    }

    x.resize(write);
    sort(x.begin(), x.end());
    return x;
}
