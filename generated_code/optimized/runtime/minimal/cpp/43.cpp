#include <vector>
#include <unordered_set>
using namespace std;

bool pairs_sum_to_zero(vector<int> l) {
    unordered_set<int> seen;
    seen.reserve(l.size() * 2);

    for (int x : l) {
        if (seen.find(-x) != seen.end()) return true;
        seen.insert(x);
    }
    return false;
}
