#include <vector>
#include <unordered_map>
using namespace std;

int search(vector<int> lst) {
    if (lst.empty()) return -1;

    unordered_map<int, int> freq;
    freq.reserve(lst.size());

    int maxVal = -1;

    for (int x : lst) {
        int cnt = ++freq[x];

        if (x > 1) {
            if (cnt >= x && x > maxVal) maxVal = x;
        } else if (x == 1) {
            if (maxVal < 1) maxVal = 1;
        } else if (x == 0) {
            if (cnt >= 2 && maxVal < 0) maxVal = 0;
        }
    }

    return maxVal;
}
