#include <vector>
#include <limits>
using namespace std;

float max_element(vector<float> l) {
    const size_t n = l.size();
    if (n == 0) return -numeric_limits<float>::infinity();

    const float* data = l.data();
    float mx = data[0];
    for (size_t i = 1; i < n; ++i) {
        if (data[i] > mx) mx = data[i];
    }
    return mx;
}
