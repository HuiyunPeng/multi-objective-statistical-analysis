#include <vector>
#include <string>

using namespace std;

vector<string> all_prefixes(string str) {
    const size_t n = str.size();
    vector<string> out;
    out.reserve(n);

    string current;
    current.reserve(n);

    for (char c : str) {
        current.push_back(c);
        out.emplace_back(current);
    }

    return out;
}
