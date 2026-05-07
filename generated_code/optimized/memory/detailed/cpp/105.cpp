#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> by_length(vector<int> arr) {
    static const char* const words[] = {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };

    sort(arr.begin(), arr.end());

    vector<string> out;
    out.reserve(arr.size());

    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        const int v = *it;
        if (v > 9) continue;
        if (v < 1) break;
        out.emplace_back(words[v]);
    }

    return out;
}
