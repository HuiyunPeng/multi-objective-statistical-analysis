#include <vector>
#include <algorithm>
using namespace std;

float median(vector<float> l) {
    const size_t n = l.size();
    if (n == 0) return 0.0f;

    const size_t mid = n / 2;
    auto midIt = l.begin() + mid;
    nth_element(l.begin(), midIt, l.end());

    if (n & 1) {
        return *midIt;
    }

    const float upper = *midIt;
    const float lower = *max_element(l.begin(), midIt);
    return 0.5f * (lower + upper);
}
