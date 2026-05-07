#include <vector>
#include <algorithm>
using namespace std;

vector<float> sort_even(vector<float> l) {
    vector<float> even;
    even.reserve((l.size() + 1) / 2);

    for (size_t i = 0; i < l.size(); i += 2)
        even.push_back(l[i]);

    sort(even.begin(), even.end());

    for (size_t i = 0, j = 0; i < l.size(); i += 2, ++j)
        l[i] = even[j];

    return l;
}
