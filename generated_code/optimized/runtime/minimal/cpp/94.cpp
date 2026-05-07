#include <vector>
using namespace std;

static inline bool isPrimeLikeOriginal(int n) {
    if (n == 1) return true;
    if (n == 2) return true;
    if ((n & 1) == 0) return false;
    for (int d = 3; 1LL * d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

int skjkasdkd(vector<int> lst) {
    int largest = 0;

    for (int x : lst) {
        if (x > largest && isPrimeLikeOriginal(x)) {
            largest = x;
        }
    }

    int sum = 0;
    while (largest > 0) {
        sum += largest % 10;
        largest /= 10;
    }
    return sum;
}
