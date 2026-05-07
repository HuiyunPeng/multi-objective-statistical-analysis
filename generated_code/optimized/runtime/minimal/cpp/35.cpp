#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

float max_element(vector<float> l) {
    if (l.empty()) return numeric_limits<float>::lowest();
    return *std::max_element(l.data(), l.data() + l.size());
}
