#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

vector<int> common(vector<int> l1, vector<int> l2) {
    unordered_set<int> in_l2;
    in_l2.reserve(l2.size() * 2 + 1);
    for (int x : l2) {
        in_l2.insert(x);
    }

    unordered_set<int> seen;
    seen.reserve(l1.size() * 2 + 1);

    vector<int> out;
    out.reserve(min(l1.size(), l2.size()));

    for (int x : l1) {
        if (in_l2.find(x) != in_l2.end() && seen.insert(x).second) {
            out.push_back(x);
        }
    }

    sort(out.begin(), out.end());
    return out;
}
