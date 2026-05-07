#include <string>
#include <algorithm>
using namespace std;

string anti_shuffle(string s) {
    int n = (int)s.size();
    int i = 0;

    while (i < n && s[i] == ' ') ++i;
    int start = i;

    while (i < n) {
        int j = i;
        while (j < n && s[j] != ' ') ++j;
        sort(s.begin() + i, s.begin() + j);
        i = j;
        while (i < n && s[i] == ' ') ++i;
    }

    if (start >= n) return "";
    if (start == 0) return s;
    return s.substr(start);
}
