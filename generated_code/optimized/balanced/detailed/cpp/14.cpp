#include <vector>
#include <string>

using namespace std;

vector<string> all_prefixes(string str) {
    const size_t n = str.size();
    vector<string> out;
    out.reserve(n);

    const char* data = str.data();
    for (size_t i = 1; i <= n; ++i) {
        out.emplace_back(data, i);
    }

    return out;
}
