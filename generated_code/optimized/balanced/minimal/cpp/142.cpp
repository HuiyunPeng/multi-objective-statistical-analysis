#include <vector>

int sum_squares(std::vector<int> lst) {
    int sum = 0;
    const int* p = lst.data();
    const std::size_t n = lst.size();
    std::size_t i = 0;

    for (; i + 11 < n; i += 12, p += 12) {
        int v;

        v = p[0];  sum += v * v;
        sum += p[1];
        sum += p[2];
        v = p[3];  sum += v * v;
        v = p[4];  sum += v * v * v;
        sum += p[5];
        v = p[6];  sum += v * v;
        sum += p[7];
        v = p[8];  sum += v * v * v;
        v = p[9];  sum += v * v;
        sum += p[10];
        sum += p[11];
    }

    for (; i < n; ++i, ++p) {
        const int v = *p;
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
