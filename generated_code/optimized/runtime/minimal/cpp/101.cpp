#include <vector>
#include <string>
using namespace std;

vector<string> words_string(string s) {
    vector<string> out;
    const size_t n = s.size();
    size_t i = 0;

    while (i < n) {
        while (i < n && (s[i] == ' ' || s[i] == ',')) ++i;
        const size_t start = i;
        while (i < n && s[i] != ' ' && s[i] != ',') ++i;
        if (start < i) out.emplace_back(s, start, i - start);
    }

    return out;
}
