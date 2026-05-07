#include <vector>
using namespace std;

int sum_squares(vector<int> lst) {
    int sum = 0;
    const int* p = lst.data();
    const int n = static_cast<int>(lst.size());
    int i = 0;

    for (; i + 11 < n; i += 12, p += 12) {
        sum += p[0] * p[0];
        sum += p[1];
        sum += p[2];
        sum += p[3] * p[3];
        sum += p[4] * p[4] * p[4];
        sum += p[5];
        sum += p[6] * p[6];
        sum += p[7];
        sum += p[8] * p[8] * p[8];
        sum += p[9] * p[9];
        sum += p[10];
        sum += p[11];
    }

    for (; i < n; ++i, ++p) {
        switch (i % 12) {
            case 0:
            case 3:
            case 6:
            case 9:
                sum += (*p) * (*p);
                break;
            case 4:
            case 8:
                sum += (*p) * (*p) * (*p);
                break;
            default:
                sum += *p;
                break;
        }
    }

    return sum;
}
