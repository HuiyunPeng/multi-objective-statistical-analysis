#include <vector>
using namespace std;

vector<float> get_positive(vector<float> l) {
    size_t j = 0;
    const size_t n = l.size();
    float* data = l.data();

    for (size_t i = 0; i < n; ++i) {
        const float v = data[i];
        if (v > 0) {
            data[j++] = v;
        }
    }

    l.resize(j);
    return l;
}
