#include <vector>
using namespace std;

int prod_signs(vector<int> arr) {
    const size_t n = arr.size();
    if (n == 0) return -32768;

    int sum = 0;
    int sign = 1;
    const int* p = arr.data();
    const int* end = p + n;

    while (p != end) {
        const int x = *p++;
        if (x == 0) return 0;
        if (x < 0) {
            sum -= x;
            sign = -sign;
        } else {
            sum += x;
        }
    }

    return sum * sign;
}
