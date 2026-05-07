#include <vector>
#include <array>
using namespace std;

int count_nums(vector<int> n) {
    static const array<unsigned char, 10000> digit_sum = [] {
        array<unsigned char, 10000> a{};
        for (int i = 1; i < 10000; ++i) {
            a[i] = static_cast<unsigned char>(a[i / 10] + (i % 10));
        }
        return a;
    }();

    int num = 0;
    const int* data = n.data();
    const size_t sz = n.size();

    for (size_t i = 0; i < sz; ++i) {
        const int x = data[i];
        if (x > 0) {
            ++num;
        } else {
            unsigned int t = 0u - static_cast<unsigned int>(x);
            unsigned int sum = 0;

            while (t >= 10000u) {
                sum += digit_sum[t % 10000u];
                t /= 10000u;
            }
            sum += digit_sum[t];

            unsigned int lead = t;
            while (lead >= 10u) {
                lead /= 10u;
            }

            if (sum > (lead << 1)) {
                ++num;
            }
        }
    }

    return num;
}
