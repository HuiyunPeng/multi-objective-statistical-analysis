#include <vector>
#include <algorithm>

using namespace std;

vector<int> unique_digits(vector<int> x) {
    size_t write = 0;

    for (int num : x) {
        if (num == 0) continue;

        bool ok = true;
        if (num > 0) {
            int n = num;
            while (n > 0) {
                if ((n & 1) == 0) {
                    ok = false;
                    break;
                }
                n /= 10;
            }
        }

        if (ok) x[write++] = num;
    }

    x.resize(write);
    if (write > 1) sort(x.begin(), x.end());
    return x;
}
