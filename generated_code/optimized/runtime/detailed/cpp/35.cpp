#include <vector>
using namespace std;

float max_element(vector<float> l) {
    const size_t n = l.size();
    const float* data = l.data();
    float maxv = -10000.0f;

    size_t i = 0;
    for (; i + 3 < n; i += 4) {
        const float a = data[i];
        const float b = data[i + 1];
        const float c = data[i + 2];
        const float d = data[i + 3];

        if (a > maxv) maxv = a;
        if (b > maxv) maxv = b;
        if (c > maxv) maxv = c;
        if (d > maxv) maxv = d;
    }

    for (; i < n; ++i) {
        if (data[i] > maxv) maxv = data[i];
    }

    return maxv;
}
