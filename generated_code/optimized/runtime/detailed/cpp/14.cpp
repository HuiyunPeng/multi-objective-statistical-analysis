#include <vector>
#include <string>

using namespace std;

vector<string> all_prefixes(string str) {
    const size_t n = str.size();
    vector<string> out;
    out.reserve(n);

    string current;
    current.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        current.push_back(str[i]);
        out.push_back(current);
    }

    return out;
}
