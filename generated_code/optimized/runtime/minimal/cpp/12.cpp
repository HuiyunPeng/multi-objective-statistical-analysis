#include <vector>
#include <string>

using namespace std;

string longest(vector<string> strings) {
    const string* best = nullptr;
    size_t bestLen = 0;

    for (const string& s : strings) {
        const size_t len = s.size();
        if (len > bestLen) {
            bestLen = len;
            best = &s;
        }
    }

    return best ? *best : string();
}
