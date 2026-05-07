#include <vector>
#include <string>
using namespace std;

string longest(vector<string> strings) {
    if (strings.empty()) return {};

    size_t bestIndex = 0;
    size_t bestLength = strings[0].size();
    const size_t n = strings.size();

    for (size_t i = 1; i < n; ++i) {
        const size_t len = strings[i].size();
        if (len > bestLength) {
            bestLength = len;
            bestIndex = i;
        }
    }

    return strings[bestIndex];
}
