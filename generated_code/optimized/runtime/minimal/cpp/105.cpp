#include <vector>
#include <string>
using namespace std;

vector<string> by_length(vector<int> arr) {
    int counts[10] = {0};
    size_t valid = 0;

    for (int x : arr) {
        if ((unsigned)(x - 1) < 9u) {
            ++counts[x];
            ++valid;
        }
    }

    vector<string> out;
    out.reserve(valid);

    static const char* names[10] = {
        "", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };

    for (int i = 9; i >= 1; --i) {
        if (counts[i]) {
            out.insert(out.end(), counts[i], string(names[i]));
        }
    }

    return out;
}
