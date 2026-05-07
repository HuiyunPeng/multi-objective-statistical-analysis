#include <vector>
using std::vector;

int count_nums(vector<int> n) {
    int num = 0;

    for (int value : n) {
        if (value > 0) {
            ++num;
        } else {
            long long w = value < 0 ? -(long long)value : 0;
            int sum = 0;

            while (w >= 10) {
                sum += static_cast<int>(w % 10);
                w /= 10;
            }

            if (sum > static_cast<int>(w)) {
                ++num;
            }
        }
    }

    return num;
}
