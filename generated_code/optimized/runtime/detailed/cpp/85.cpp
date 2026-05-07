#include <vector>
using namespace std;

int add(vector<int> lst) {
    int sum = 0;
    const size_t n = lst.size();
    for (size_t i = 1; i < n; i += 2) {
        const int v = lst[i];
        if ((v & 1) == 0) sum += v;
    }
    return sum;
}
