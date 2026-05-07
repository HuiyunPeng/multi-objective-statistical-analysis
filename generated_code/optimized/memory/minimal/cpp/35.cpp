#include <vector>
#include <limits>
using namespace std;

float max_element(vector<float> l) {
    float mx = numeric_limits<float>::lowest();
    for (size_t i = 0, n = l.size(); i < n; ++i) {
        if (l[i] > mx) mx = l[i];
    }
    return mx;
}
