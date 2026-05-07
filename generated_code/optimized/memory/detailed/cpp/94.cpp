#include <vector>
using namespace std;

int skjkasdkd(vector<int> lst) {
    int largest = 0;

    for (int x : lst) {
        if (x <= largest || x < 2) continue;

        bool prime = true;
        for (int j = 2; j * j <= x; ++j) {
            if (x % j == 0) {
                prime = false;
                break;
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
