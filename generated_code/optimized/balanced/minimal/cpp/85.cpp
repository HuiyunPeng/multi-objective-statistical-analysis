#include <vector>
using std::vector;

int add(vector<int> lst) {
    int sum = 0;
    const int* p = lst.data();
    const int* end = p + lst.size();

    for (p += 1; p < end; p += 2) {
        const int v = *p;
        if ((static_cast<unsigned int>(v) & 1u) == 0u) {
            sum += v;
        }
    }

    return sum;
}
