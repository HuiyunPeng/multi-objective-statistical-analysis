#include <vector>
using std::vector;

int count_nums(vector<int> n) {
    int num = 0;
    const int* p = n.data();
    const int* const end = p + n.size();

    for (; p != end; ++p) {
        const int x = *p;

        if (x > 0) {
            ++num;
        } else if (x <= -10) {
            unsigned int w = static_cast<unsigned int>(-(static_cast<long long>(x)));
            int sum = 0;

            do {
                sum += static_cast<int>(w % 10);
                w /= 10;
            } while (w >= 10);

            if (sum > static_cast<int>(w)) {
                ++num;
            }
        }
    }

    return num;
}
