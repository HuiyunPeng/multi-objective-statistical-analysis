#include <vector>

std::vector<int> eat(int number, int need, int remaining) {
    const int consumed = (need < remaining) ? need : remaining;
    return {number + consumed, remaining - consumed};
}
