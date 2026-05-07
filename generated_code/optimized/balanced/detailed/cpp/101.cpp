#include <string>
#include <vector>

using namespace std;

vector<string> words_string(string s) {
    vector<string> out;
    const size_t n = s.size();
    size_t start = 0;

    for (size_t i = 0; i < n; ++i) {
        if (s[i] == ' ' || s[i] == ',') {
            if (i > start) {
                out.emplace_back(s, start, i - start);
            }
            start = i + 1;
        }
    }

    if (start < n) {
        out.emplace_back(s, start, n - start);
    }

    return out;
}
