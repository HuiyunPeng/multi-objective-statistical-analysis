#include <vector>
#include <algorithm>
using namespace std;

vector<float> sort_even(vector<float> l) {
    const size_t n = l.size();
    vector<float> even;
    even.reserve((n + 1) / 2);

    for (size_t i = 0; i < n; i += 2)
        even.push_back(l[i]);

    sort(even.begin(), even.end());

    for (size_t i = 0, j = 0; i < n; i += 2, ++j)
        l[i] = even[j];

    return l;
}
