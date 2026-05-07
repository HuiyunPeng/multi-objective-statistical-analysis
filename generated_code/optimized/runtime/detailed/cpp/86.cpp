#include <string>
#include <algorithm>
using namespace std;

string anti_shuffle(string s) {
    const size_t n = s.size();
    size_t start = 0;

    while (start < n && s[start] == ' ') ++start;

    size_t i = start;
    while (i < n) {
        while (i < n && s[i] == ' ') ++i;
        size_t j = i;
        while (j < n && s[j] != ' ') ++j;
        if (j > i) sort(s.begin() + i, s.begin() + j);
        i = j;
    }

    return start ? s.substr(start) : s;
}
