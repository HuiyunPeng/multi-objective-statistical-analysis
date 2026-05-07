#include <string>
#include <algorithm>

using namespace std;

string anti_shuffle(string s) {
    const size_t n = s.size();
    size_t first_non_space = string::npos;

    size_t i = 0;
    while (i < n) {
        while (i < n && s[i] == ' ') ++i;
        if (i == n) break;

        if (first_non_space == string::npos) first_non_space = i;

        size_t j = i + 1;
        while (j < n && s[j] != ' ') ++j;

        sort(s.begin() + i, s.begin() + j);
        i = j;
    }

    if (first_non_space == string::npos) return "";
    if (first_non_space != 0) s.erase(0, first_non_space);
    return s;
}
