#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
#include <algorithm>
#include <stdlib.h>

vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    if (prefix.empty()) return strings;

    vector<string> out;
    const size_t prefix_len = prefix.size();

    for (size_t i = 0, n = strings.size(); i < n; ++i) {
        string& s = strings[i];
        if (s.size() >= prefix_len && s.compare(0, prefix_len, prefix) == 0) {
            out.emplace_back(std::move(s));
        }
    }

    return out;
}
