#include <vector>
using namespace std;

int solutions(vector<int> lst) {
    int sum = 0;
    for (size_t i = 0, n = lst.size(); i < n; i += 2) {
        int v = lst[i];
        if (v & 1) sum += v;
    }
    return sum;
}
