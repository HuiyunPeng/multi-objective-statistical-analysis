#include <vector>
#include <string>
using namespace std;

vector<string> by_length(vector<int> arr) {
    static const string names[10] = {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };

    int freq[10] = {0};
    int validCount = 0;

    for (int x : arr) {
        if (x >= 1 && x <= 9) {
            ++freq[x];
            ++validCount;
        }
    }

    vector<string> out;
    out.reserve(validCount);

    for (int i = 9; i >= 1; --i) {
        for (int c = freq[i]; c > 0; --c) {
            out.push_back(names[i]);
        }
    }

    return out;
}
