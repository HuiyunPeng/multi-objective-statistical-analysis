#include <vector>
#include <string>

using namespace std;

vector<string> words_string(string s) {
    vector<string> out;
    const size_t n = s.size();
    size_t i = 0;

    while (i < n) {
        while (i < n && (s[i] == ' ' || s[i] == ',')) ++i;
        if (i >= n) break;

        size_t j = i;
        while (j < n && s[j] != ' ' && s[j] != ',') ++j;

        out.emplace_back(s.substr(i, j - i));
        i = j;
    }

    return out;
}
