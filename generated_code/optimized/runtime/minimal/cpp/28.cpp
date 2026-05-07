#include <vector>
#include <string>

using namespace std;

string concatenate(vector<string> strings) {
    size_t total = 0;
    for (const auto& s : strings) {
        total += s.size();
    }

    string out;
    out.reserve(total);
    for (const auto& s : strings) {
        out += s;
    }

    return out;
}
