#include <vector>
#include <string>
using namespace std;

vector<string> by_length(vector<int> arr) {
    static const string words[10] = {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };

    int counts[10] = {};
    size_t valid = 0;

    for (int x : arr) {
        if ((unsigned)(x - 1) < 9u) {
            ++counts[x];
            ++valid;
        }
    }

    vector<string> out;
    out.reserve(valid);

    for (int d = 9; d >= 1; --d) {
        for (int c = counts[d]; c > 0; --c) {
            out.push_back(words[d]);
        }
    }

    return out;
}
