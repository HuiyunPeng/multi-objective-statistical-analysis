#include <vector>
#include <cstdlib>
using namespace std;

int prod_signs(vector<int> arr) {
    if (arr.empty()) return -32768;

    int sum = 0;
    int sign = 1;

    for (int x : arr) {
        if (x == 0) return 0;
        sum += abs(x);
        if (x < 0) sign = -sign;
    }

    return sum * sign;
}
