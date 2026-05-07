#include <string>
#include <map>

using namespace std;

map<char, int> histogram(string test) {
    int counts[256] = {0};
    int maxCount = 0;

    for (char c : test) {
        if (c != ' ') {
            int& cnt = counts[static_cast<unsigned char>(c)];
            ++cnt;
            if (cnt > maxCount) {
                maxCount = cnt;
            }
        }
    }

    map<char, int> out;
    if (maxCount == 0) {
        return out;
    }

    for (int i = 0; i < 256; ++i) {
        if (counts[i] == maxCount) {
            out[static_cast<char>(i)] = maxCount;
        }
    }

    return out;
}
