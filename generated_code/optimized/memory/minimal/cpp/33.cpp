#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_third(vector<int> l) {
    vector<int> third;
    third.reserve((l.size() + 2) / 3);

    for (size_t i = 0; i < l.size(); i += 3) {
        third.push_back(l[i]);
    }

    sort(third.begin(), third.end());

    for (size_t i = 0, j = 0; i < l.size(); i += 3, ++j) {
        l[i] = third[j];
    }

    return l;
}
