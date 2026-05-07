#include <vector>
using namespace std;

int count_nums(vector<int> n) {
    int num = 0;
    const size_t sz = n.size();

    for (size_t i = 0; i < sz; ++i) {
        const int x = n[i];
        if (x > 0) {
            ++num;
        } else {
            long long w = x;
            if (w < 0) w = -w;

            int sum = 0;
            while (w >= 10) {
                sum += static_cast<int>(w % 10);
                w /= 10;
            }

            if (sum > w) ++num;
        }
    }

    return num;
}
