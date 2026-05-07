#include <vector>
#include <string>

using namespace std;

string concatenate(vector<string> strings) {
    size_t totalSize = 0;
    const size_t n = strings.size();
    for (size_t i = 0; i < n; ++i) {
        totalSize += strings[i].size();
    }

    string out;
    out.reserve(totalSize);
    for (size_t i = 0; i < n; ++i) {
        out += strings[i];
    }

    return out;
}
