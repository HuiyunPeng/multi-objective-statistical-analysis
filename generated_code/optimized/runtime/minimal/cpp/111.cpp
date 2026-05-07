#include <map>
#include <string>
using namespace std;

map<char, int> histogram(string test) {
    int freq[256] = {0};
    int maxCount = 0;

    for (unsigned char c : test) {
        if (c != ' ') {
            int newCount = ++freq[c];
            if (newCount > maxCount) maxCount = newCount;
        }
    }

    map<char, int> out;
    if (maxCount == 0) return out;

    for (int i = 0; i < 256; ++i) {
        if (freq[i] == maxCount) {
            out[static_cast<char>(i)] = maxCount;
        }
    }

    return out;
}
