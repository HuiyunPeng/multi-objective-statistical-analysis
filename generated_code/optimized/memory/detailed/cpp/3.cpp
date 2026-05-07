#include <vector>
using namespace std;

bool below_zero(vector<int> operations) {
    int sum = 0;
    for (int value : operations) {
        sum += value;
        if (sum < 0) return true;
    }
    return false;
}
