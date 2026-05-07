#include <vector>
using namespace std;

int sum_squares(vector<int> lst) {
    int sum = 0;
    const int n = static_cast<int>(lst.size());
    const int* a = lst.data();
    int i = 0;

    for (; i + 11 < n; i += 12) {
        int v;

        v = a[i];      sum += v * v;       // i % 12 == 0
        sum += a[i+1];                     // 1
        sum += a[i+2];                     // 2
        v = a[i+3];  sum += v * v;         // 3
        v = a[i+4];  sum += v * v * v;     // 4
        sum += a[i+5];                     // 5
        v = a[i+6];  sum += v * v;         // 6
        sum += a[i+7];                     // 7
        v = a[i+8];  sum += v * v * v;     // 8
        v = a[i+9];  sum += v * v;         // 9
        sum += a[i+10];                    // 10
        sum += a[i+11];                    // 11
    }

    for (; i < n; ++i) {
        const int mod = i % 12;
        const int v = a[i];
        if (mod == 0 || mod == 3 || mod == 6 || mod == 9) {
            sum += v * v;
        } else if (mod == 4 || mod == 8) {
            sum += v * v * v;
        } else {
            sum += v;
        }
    }

    return sum;
}
