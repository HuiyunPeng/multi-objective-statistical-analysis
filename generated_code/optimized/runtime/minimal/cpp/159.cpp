#include <vector>
using namespace std;

vector<int> eat(int number, int need, int remaining) {
    const int eaten = (need < remaining) ? need : remaining;
    return {number + eaten, remaining - eaten};
}
