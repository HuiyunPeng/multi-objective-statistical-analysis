#include <vector>
using namespace std;

int skjkasdkd(vector<int> lst) {
    int largest = 0;

    for (int x : lst) {
        if (x <= largest || x <= 1) continue;

        bool prime = true;
        if (x > 3) {
            if ((x & 1) == 0 || x % 3 == 0) {
                prime = false;
            } else {
                for (int d = 5; 1LL * d * d <= x; d += 6) {
                    if (x % d == 0 || x % (d + 2) == 0) {
                        prime = false;
                        break;
                    }
                }
            }
        }

        if (prime) largest = x;
    }

    int sum = 0;
    while (largest > 0) {
        sum += largest % 10;
        largest /= 10;
    }
    return sum;
}

#undef NDEBUG
#include <assert.h>
