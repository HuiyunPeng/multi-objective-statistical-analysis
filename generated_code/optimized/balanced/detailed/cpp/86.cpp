#include <string>
#include <algorithm>

using namespace std;

string anti_shuffle(string s) {
    const size_t n = s.size();
    size_t word_start = string::npos;

    for (size_t i = 0; i <= n; ++i) {
        if (i < n && s[i] != ' ') {
            if (word_start == string::npos) word_start = i;
        } else if (word_start != string::npos) {
            sort(s.begin() + word_start, s.begin() + i);
            word_start = string::npos;
        }
    }

    const size_t first = s.find_first_not_of(' ');
    if (first == string::npos) return "";
    if (first == 0) return s;
    return s.substr(first);
}
