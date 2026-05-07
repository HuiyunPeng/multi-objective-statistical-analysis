#include <vector>
using namespace std;

int count_nums(vector<int> n) {
    static const int* digitSum = []() -> const int* {
        static int ds[10000] = {};
        for (int i = 1; i < 10000; ++i) ds[i] = ds[i / 10] + (i % 10);
        return ds;
    }();

    int num = 0;
    const int* data = n.data();
    const size_t sz = n.size();

    for (size_t i = 0; i < sz; ++i) {
        const int x = data[i];

        if (x > 0) {
            ++num;
            continue;
        }

        if (x > -10) continue;

        const unsigned int mag = static_cast<unsigned int>(-(long long)x);

        const int total =
            digitSum[mag % 10000u] +
            digitSum[(mag / 10000u) % 10000u] +
            digitSum[mag / 100000000u];

        unsigned int msd;
        if (mag >= 100000000u) {
            const unsigned int high = mag / 100000000u;
            msd = (high >= 10u) ? (high / 10u) : high;
        } else if (mag >= 10000u) {
            const unsigned int high = mag / 10000u;
            if (high >= 1000u) msd = high / 1000u;
            else if (high >= 100u) msd = high / 100u;
            else if (high >= 10u) msd = high / 10u;
            else msd = high;
        } else {
            if (mag >= 1000u) msd = mag / 1000u;
            else if (mag >= 100u) msd = mag / 100u;
            else msd = mag / 10u;
        }

        if (total > static_cast<int>(msd << 1)) ++num;
    }

    return num;
}
