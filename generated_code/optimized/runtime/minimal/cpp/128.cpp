#include <vector>
using namespace std;

int prod_signs(vector<int> arr) {
    const size_t n = arr.size();
    if (n == 0) return -32768;

    int sum = 0;
    bool hasZero = false;
    bool negativeParity = false;

    const int* p = arr.data();
    const int* end = p + n;

    while (p != end) {
        const int v = *p++;
        sum += (v < 0) ? -v : v;
        hasZero |= (v == 0);
        negativeParity ^= (v < 0);
    }

    if (hasZero) return 0;
    return negativeParity ? -sum : sum;
}
