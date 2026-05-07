#include <vector>

std::vector<int> eat(int number, int need, int remaining) {
    const int eaten = (need > remaining) ? remaining : need;
    return {number + eaten, remaining - eaten};
}
