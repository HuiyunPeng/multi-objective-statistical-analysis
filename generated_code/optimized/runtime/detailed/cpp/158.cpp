#include <vector>
#include <string>
#include <cstdint>
using namespace std;

string find_max(vector<string> words) {
    string best = "";
    size_t bestUnique = 0;

    const size_t wordCount = words.size();
    for (size_t i = 0; i < wordCount; ++i) {
        const string& w = words[i];
        const size_t len = w.size();

        if (len < bestUnique) continue;

        uint64_t masks[4] = {0, 0, 0, 0};
        size_t uniqueCount = 0;

        for (size_t j = 0; j < len; ++j) {
            const unsigned char c = static_cast<unsigned char>(w[j]);
            const uint64_t bit = 1ULL << (c & 63);
            uint64_t& mask = masks[c >> 6];

            if ((mask & bit) == 0) {
                mask |= bit;
                ++uniqueCount;
            }

            if (uniqueCount + (len - j - 1) < bestUnique) break;
        }

        if (uniqueCount > bestUnique || (uniqueCount == bestUnique && w < best)) {
            best = w;
            bestUnique = uniqueCount;
        }
    }

    return best;
}
