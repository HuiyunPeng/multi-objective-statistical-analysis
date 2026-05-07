#include <vector>
#include <cstdlib>

using std::vector;

int count_nums(vector<int> n) {
    int num = 0;
    for (size_t i = 0, sz = n.size(); i < sz; ++i) {
        int x = n[i];
        if (x > 0) {
            ++num;
        } else {
            int sum = 0;
            int w = x < 0 ? -x : x;
            while (w >= 10) {
                sum += w % 10;
                w /= 10;
            }
            sum -= w;
            if (sum > 0) {
                ++num;
            }
        }
    }
    return num;
}
