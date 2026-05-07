#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_third(vector<int> l) {
    const size_t n = l.size();
    const size_t m = (n + 2) / 3;
    if (m < 2) return l;

    vector<int> third(m);
    for (size_t i = 0, j = 0; i < n; i += 3, ++j) {
        third[j] = l[i];
    }

    sort(third.begin(), third.end());

    for (size_t i = 0, j = 0; i < n; i += 3, ++j) {
        l[i] = third[j];
    }

    return l;
}
