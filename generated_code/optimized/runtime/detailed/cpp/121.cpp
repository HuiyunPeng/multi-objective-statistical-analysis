#include <vector>
using namespace std;

int solutions(vector<int> lst) {
    int sum = 0;
    const size_t n = lst.size();
    const int* data = lst.data();

    for (size_t i = 0; i < n; i += 2) {
        const int v = data[i];
        if (v % 2 == 1) sum += v;
    }

    return sum;
}
