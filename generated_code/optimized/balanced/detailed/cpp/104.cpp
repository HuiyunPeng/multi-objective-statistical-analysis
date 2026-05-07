#include <vector>
#include <algorithm>

using namespace std;

vector<int> unique_digits(vector<int> x) {
    size_t write = 0;
    const size_t n = x.size();

    for (size_t i = 0; i < n; ++i) {
        int num = x[i];
        bool keep;

        if (num < 0) {
            keep = true;
        } else if (num == 0) {
            keep = false;
        } else {
            keep = true;
            while (num > 0) {
                if ((num & 1) == 0) {
                    keep = false;
                    break;
                }
                num /= 10;
            }
        }

        if (keep) {
            x[write++] = x[i];
        }
    }

    x.resize(write);
    if (write > 1) {
        sort(x.begin(), x.end());
    }
    return x;
}
