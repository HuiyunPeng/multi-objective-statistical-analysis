#include <string>
#include <vector>
using namespace std;

string find_max(vector<string> words) {
    string max = "";
    int maxu = 0;

    for (const string& w : words) {
        bool seen[256] = {false};
        int uniqueCount = 0;

        for (unsigned char c : w) {
            if (!seen[c]) {
                seen[c] = true;
                ++uniqueCount;
            }
        }

        if (uniqueCount > maxu || (uniqueCount == maxu && w < max)) {
            max = w;
            maxu = uniqueCount;
        }
    }

    return max;
}
