#include <vector>
#include <string>

using namespace std;

vector<string> by_length(vector<int> arr) {
    static const char* const names[10] = {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };

    int counts[10] = {0};
    size_t total = 0;

    for (int x : arr) {
        if (static_cast<unsigned>(x - 1) < 9u) {
            ++counts[x];
            ++total;
        }
    }

    vector<string> out;
    out.reserve(total);

    for (int v = 9; v >= 1; --v) {
        for (int c = counts[v]; c > 0; --c) {
            out.emplace_back(names[v]);
        }
    }

    return out;
}
