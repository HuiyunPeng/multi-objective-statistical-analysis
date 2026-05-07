#include <vector>
#include <algorithm>
using namespace std;

vector<float> sort_even(vector<float> l) {
    const size_t even_count = (l.size() + 1) / 2;
    vector<float> even;
    even.reserve(even_count);

    for (size_t i = 0; i < l.size(); i += 2) {
        even.push_back(l[i]);
    }

    sort(even.begin(), even.end());

    for (size_t i = 0, j = 0; i < l.size(); i += 2, ++j) {
        l[i] = even[j];
    }

    return l;
}
