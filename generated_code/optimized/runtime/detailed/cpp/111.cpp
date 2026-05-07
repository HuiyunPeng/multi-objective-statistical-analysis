#include <string>
#include <map>

using namespace std;

map<char,int> histogram(string test) {
    int counts[256] = {0};
    int maxCount = 0;

    const size_t n = test.size();
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = static_cast<unsigned char>(test[i]);
        if (c != ' ') {
            int newCount = ++counts[c];
            if (newCount > maxCount) maxCount = newCount;
        }
    }

    map<char,int> out;
    if (maxCount == 0) return out;

    for (int i = 0; i < 256; ++i) {
        if (counts[i] == maxCount) {
            out[static_cast<char>(i)] = maxCount;
        }
    }

    return out;
}
