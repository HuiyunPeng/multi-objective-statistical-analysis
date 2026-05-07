#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
#include <algorithm>
#include <stdlib.h>
#include <utility>

vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    vector<string> out;
    const size_t prefix_len = prefix.size();

    for (string& s : strings) {
        if (s.size() >= prefix_len && s.compare(0, prefix_len, prefix) == 0) {
            out.push_back(std::move(s));
        }
    }

    return out;
}
