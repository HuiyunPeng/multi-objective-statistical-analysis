#include <vector>
using namespace std;

int sum_squares(vector<int> lst) {
    int sum = 0;
    const size_t n = lst.size();
    for (size_t i = 0; i < n; ++i) {
        const int x = lst[i];
        if (i % 3 == 0) sum += x * x;
        else if (i % 4 == 0) sum += x * x * x;
        else sum += x;
    }
    return sum;
}
