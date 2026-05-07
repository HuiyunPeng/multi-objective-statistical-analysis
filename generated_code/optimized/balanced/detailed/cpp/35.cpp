#include <vector>
#include <limits>

using namespace std;

float max_element(vector<float> l) {
    const size_t n = l.size();
    if (n == 0) {
        return -numeric_limits<float>::infinity();
    }

    const float* p = l.data();
    float mx = p[0];
    for (size_t i = 1; i < n; ++i) {
        if (p[i] > mx) mx = p[i];
    }
    return mx;
}
