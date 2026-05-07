#include <vector>
using namespace std;

int skjkasdkd(vector<int> lst) {
    int largest = 0;

    for (int x : lst) {
        if (x <= largest || x < 2) continue;

        bool prime = true;
        if ((x & 1) == 0) {
            prime = (x == 2);
        } else if (x % 3 == 0) {
            prime = (x == 3);
        } else {
            for (int d = 5; d <= x / d; d += 6) {
                if (x % d == 0 || x % (d + 2) == 0) {
                    prime = false;
                    break;
                }
            }
        }

        if (prime) largest = x;
    }

    int sum = 0;
    for (int x = largest; x > 0; x /= 10) {
        sum += x % 10;
    }
    return sum;
}
