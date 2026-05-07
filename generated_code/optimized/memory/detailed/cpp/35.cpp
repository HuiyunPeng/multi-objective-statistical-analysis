#include <vector>
using namespace std;

float max_element(vector<float> l) {
    if (l.empty()) return -10000.0f;

    const float* p = l.data();
    const float* end = p + l.size();
    float max = *p++;

    while (p != end) {
        if (max < *p) max = *p;
        ++p;
    }

    return max;
}
