#include <vector>
#include <string>
#include <cstring>
using namespace std;

string find_max(vector<string> words) {
    int bestIndex = -1;
    int maxu = 0;
    bool seen[256];

    for (int i = 0; i < (int)words.size(); ++i) {
        memset(seen, 0, sizeof(seen));
        int uniqueCount = 0;
        const string& w = words[i];

        for (int j = 0; j < (int)w.size(); ++j) {
            unsigned char c = static_cast<unsigned char>(w[j]);
            if (!seen[c]) {
                seen[c] = true;
                ++uniqueCount;
            }
        }

        if (uniqueCount > maxu || (uniqueCount == maxu && (bestIndex == -1 || w < words[bestIndex]))) {
            bestIndex = i;
            maxu = uniqueCount;
        }
    }

    return bestIndex == -1 ? string() : std::move(words[bestIndex]);
}
