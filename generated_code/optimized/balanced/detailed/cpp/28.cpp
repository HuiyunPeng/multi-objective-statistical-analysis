#include <string>
#include <vector>

using namespace std;

string concatenate(vector<string> strings) {
    size_t totalSize = 0;
    for (const string& s : strings) {
        totalSize += s.size();
    }

    string out;
    out.reserve(totalSize);

    for (const string& s : strings) {
        out += s;
    }

    return out;
}
