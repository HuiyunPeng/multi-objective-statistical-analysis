#include <vector>
#include <algorithm>
using namespace std;

vector<int> unique_digits(vector<int> x) {
    size_t write = 0;

    for (size_t i = 0; i < x.size(); ++i) {
        int num = x[i];
        bool u = true;

        if (num == 0) {
            u = false;
        } else {
            while (num > 0 && u) {
                if ((num % 10) % 2 == 0) u = false;
                num /= 10;
            }
        }

        if (u) {
            x[write++] = x[i];
        }
    }

    x.resize(write);
    sort(x.begin(), x.end());
    return x;
}
