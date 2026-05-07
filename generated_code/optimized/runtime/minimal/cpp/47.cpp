#include <vector>
#include <algorithm>
using namespace std;

float median(vector<float> l) {
    const size_t n = l.size();
    const size_t mid = n / 2;

    nth_element(l.begin(), l.begin() + mid, l.end());
    const float upper = l[mid];

    if (n & 1) return upper;

    const float lower = *max_element(l.begin(), l.begin() + mid);
    return 0.5f * (lower + upper);
}
