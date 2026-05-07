#include <string>
#include <algorithm>
using namespace std;

string anti_shuffle(string s) {
    const size_t n = s.size();
    size_t i = 0;

    while (i < n && s[i] == ' ') {
        ++i;
    }
    if (i == n) {
        s.clear();
        return s;
    }

    size_t write = 0;

    while (i < n) {
        size_t word_end = i;
        while (word_end < n && s[word_end] != ' ') {
            ++word_end;
        }

        sort(s.begin() + i, s.begin() + word_end);

        for (size_t k = i; k < word_end; ++k) {
            s[write++] = s[k];
        }

        size_t space_end = word_end;
        while (space_end < n && s[space_end] == ' ') {
            ++space_end;
        }

        for (size_t k = word_end; k < space_end; ++k) {
            s[write++] = s[k];
        }

        i = space_end;
    }

    s.resize(write);
    return s;
}
