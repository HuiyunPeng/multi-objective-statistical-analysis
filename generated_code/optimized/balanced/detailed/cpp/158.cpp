#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include <math.h>
#include <stdlib.h>

string find_max(vector<string> words) {
    const size_t n = words.size();
    size_t bestIndex = n;
    int bestUnique = -1;

    unsigned int seen[256] = {};
    unsigned int stamp = 1;

    for (size_t i = 0; i < n; ++i) {
        const string& w = words[i];
        int uniqueCount = 0;

        if (stamp == 0) {
            for (int k = 0; k < 256; ++k) seen[k] = 0;
            stamp = 1;
        }

        for (size_t j = 0, m = w.size(); j < m; ++j) {
            unsigned char c = static_cast<unsigned char>(w[j]);
            if (seen[c] != stamp) {
                seen[c] = stamp;
                ++uniqueCount;
            }
        }
        ++stamp;

        if (uniqueCount > bestUnique ||
            (uniqueCount == bestUnique && (bestIndex == n || w < words[bestIndex]))) {
            bestUnique = uniqueCount;
            bestIndex = i;
        }
    }

    return bestIndex == n ? string() : words[bestIndex];
}
