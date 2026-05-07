#include <vector>
#include <string>
using namespace std;

vector<string> by_length(vector<int> arr) {
    static const char* names[] = {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"
    };

    int freq[10] = {0};
    int count = 0;

    for (int x : arr) {
        if (x >= 1 && x <= 9) {
            ++freq[x];
            ++count;
        }
    }

    vector<string> out;
    out.reserve(count);

    for (int i = 9; i >= 1; --i) {
        for (int j = 0; j < freq[i]; ++j) {
            out.push_back(names[i]);
        }
    }

    return out;
}
