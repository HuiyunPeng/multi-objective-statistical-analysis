#include <vector>
using namespace std;

int sum_squares(vector<int> lst) {
    int sum = 0;
    const int* a = lst.data();
    int n = static_cast<int>(lst.size());
    int i = 0;

    for (; i + 11 < n; i += 12) {
        int v;

        v = a[i + 0];  sum += v * v;
        sum += a[i + 1];
        sum += a[i + 2];
        v = a[i + 3];  sum += v * v;
        v = a[i + 4];  sum += v * v * v;
        sum += a[i + 5];
        v = a[i + 6];  sum += v * v;
        sum += a[i + 7];
        v = a[i + 8];  sum += v * v * v;
        v = a[i + 9];  sum += v * v;
        sum += a[i + 10];
        sum += a[i + 11];
    }

    for (; i < n; ++i) {
        int v = a[i];
        switch (i % 12) {
            case 0:
            case 3:
            case 6:
            case 9:
                sum += v * v;
                break;
            case 4:
            case 8:
                sum += v * v * v;
                break;
            default:
                sum += v;
                break;
        }
    }

    return sum;
}
