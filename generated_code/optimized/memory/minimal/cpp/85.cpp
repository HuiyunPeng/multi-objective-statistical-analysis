#include <vector>
using namespace std;

int add(vector<int> lst) {
    int sum = 0;
    const size_t n = lst.size();
    for (size_t i = 1; i < n; i += 2) {
        if ((lst[i] & 1) == 0) {
            sum += lst[i];
        }
    }
    return sum;
}
