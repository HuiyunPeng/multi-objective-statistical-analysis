#include <string>
#include <algorithm>
using namespace std;

string anti_shuffle(string s) {
    const size_t n = s.size();
    size_t first = 0;
    while (first < n && s[first] == ' ') ++first;
    if (first == n) return "";

    size_t i = first;
    while (i < n) {
        while (i < n && s[i] == ' ') ++i;
        size_t j = i;
        while (j < n && s[j] != ' ') ++j;
        if (j - i > 1) sort(s.begin() + i, s.begin() + j);
        i = j;
    }

    return s.substr(first);
}
