#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_third(vector<int> l) {
    const size_t n = l.size();
    vector<int> third;
    third.reserve((n + 2) / 3);

    for (size_t i = 0; i < n; i += 3) {
        third.push_back(l[i]);
    }

    sort(third.begin(), third.end());

    size_t j = 0;
    for (size_t i = 0; i < n; i += 3) {
        l[i] = third[j++];
    }

    return l;
}
