#include <vector>
using namespace std;

int solutions(vector<int> lst) {
    int sum = 0;
    const int n = static_cast<int>(lst.size());

    for (int i = 0; i < n; i += 2) {
        const int v = lst[i];
        if (v % 2 == 1) {
            sum += v;
        }
    }

    return sum;
}
