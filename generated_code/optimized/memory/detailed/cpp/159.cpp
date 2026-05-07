#include <vector>
using namespace std;

vector<int> eat(int number, int need, int remaining) {
    vector<int> result(2);
    if (need > remaining) {
        result[0] = number + remaining;
        result[1] = 0;
    } else {
        result[0] = number + need;
        result[1] = remaining - need;
    }
    return result;
}
