#include <string>
#include <map>
using namespace std;

map<char,int> histogram(string test) {
    int count[256] = {0};
    int maxCount = 0;

    for (char c : test) {
        if (c != ' ') {
            int &v = count[static_cast<unsigned char>(c)];
            ++v;
            if (v > maxCount) {
                maxCount = v;
            }
        }
    }

    map<char,int> out;
    if (maxCount == 0) {
        return out;
    }

    for (int i = 0; i < 256; ++i) {
        if (count[i] == maxCount) {
            out[static_cast<char>(i)] = maxCount;
        }
    }

    return out;
}
