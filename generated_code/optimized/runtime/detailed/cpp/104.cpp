#include <vector>
#include <algorithm>
using namespace std;

vector<int> unique_digits(vector<int> x) {
    vector<int> out;
    out.reserve(x.size());

    for (int num : x) {
        if (num < 0) {
            out.push_back(num);
            continue;
        }
        if (num == 0) continue;

        int n = num;
        while (n && (n & 1)) {
            n /= 10;
        }
        if (n == 0) {
            out.push_back(num);
        }
    }

    if (out.size() > 1) {
        sort(out.begin(), out.end());
    }
    return out;
}
