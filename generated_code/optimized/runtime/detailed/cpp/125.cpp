#include <string>
#include <vector>
using namespace std;

static inline vector<string> split_by_delim(const string& txt, char delim) {
    vector<string> out;
    size_t start = 0;
    const size_t n = txt.size();

    for (size_t i = 0; i < n; ++i) {
        if (txt[i] == delim) {
            if (i > start) out.emplace_back(txt.substr(start, i - start));
            start = i + 1;
        }
    }

    if (start < n) out.emplace_back(txt.substr(start));
    return out;
}

vector<string> split_words(string txt) {
    if (txt.find(' ') != string::npos) return split_by_delim(txt, ' ');
    if (txt.find(',') != string::npos) return split_by_delim(txt, ',');

    int num = 0;
    for (unsigned char c : txt) {
        num += (c >= 'a' && c <= 'z' && !(c & 1));
    }

    return {to_string(num)};
}
