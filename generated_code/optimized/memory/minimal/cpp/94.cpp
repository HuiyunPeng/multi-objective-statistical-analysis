#include <vector>
using namespace std;

int skjkasdkd(vector<int> lst) {
    int largest = 0;

    for (int x : lst) {
        if (x <= largest || x < 2) continue;

        bool prime = true;
        for (int d = 2; 1LL * d * d <= x; ++d) {
            if (x % d == 0) {
                prime = false;
                break;
            }
        }

        if (prime) largest = x;
    }

    int sum = 0;
    do {
        sum += largest % 10;
        largest /= 10;
    } while (largest > 0);

    return sum;
}
