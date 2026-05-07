#include <string>
#include <vector>

using namespace std;

string concatenate(vector<string> strings) {
    size_t total_size = 0;
    for (const auto& s : strings) {
        total_size += s.size();
    }

    string out;
    out.reserve(total_size);
    for (const auto& s : strings) {
        out += s;
    }

    return out;
}
