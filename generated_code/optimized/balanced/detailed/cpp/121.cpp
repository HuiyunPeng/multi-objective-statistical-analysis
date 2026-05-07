#include <vector>
using namespace std;

int solutions(vector<int> lst) {
    int sum = 0;
    const int* p = lst.data();
    const int* end = p + lst.size();

    for (; p < end; p += 2) {
        const int v = *p;
        if (v % 2 == 1) {
            sum += v;
        }
    }

    return sum;
}
