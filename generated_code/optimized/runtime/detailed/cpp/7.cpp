#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<string> filter_by_substring(vector<string> strings, string substring) {
    if (substring.empty()) return strings;
    if (strings.empty()) return {};

    vector<string> out;
    out.reserve(strings.size());

    for (string& s : strings) {
        if (s.find(substring) != string::npos) {
            out.push_back(std::move(s));
        }
    }

    return out;
}
