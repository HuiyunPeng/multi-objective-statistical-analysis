#include <vector>
#include <unordered_map>
using namespace std;

int search(vector<int> lst) {
    unordered_map<int, int> freq;
    freq.reserve(lst.size() * 2);

    int mx = -1;
    for (int x : lst) {
        auto it = freq.find(x);
        if (it == freq.end()) {
            freq.emplace(x, 1);
            if (mx == -1 && x == 1) mx = 1;
        } else {
            int cnt = ++(it->second);
            if (cnt >= x && x > mx) mx = x;
        }
    }
    return mx;
}
