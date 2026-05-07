#include <string>
#include <vector>
#include <cstdint>
using namespace std;

string find_max(vector<string> words) {
    string best = "";
    int maxu = 0;

    for (const string& w : words) {
        uint64_t seen[4] = {0, 0, 0, 0};
        int uniqueCount = 0;

        for (unsigned char c : w) {
            uint64_t bit = 1ULL << (c & 63);
            uint64_t& bucket = seen[c >> 6];
            if ((bucket & bit) == 0) {
                bucket |= bit;
                ++uniqueCount;
            }
        }

        if (uniqueCount > maxu || (uniqueCount == maxu && w < best)) {
            best = w;
            maxu = uniqueCount;
        }
    }

    return best;
}
