#include <string>
#include <vector>
using namespace std;

vector<string> split_words(string txt) {
    const size_t n = txt.size();

    if (txt.find(' ') != string::npos) {
        vector<string> out;
        size_t start = 0;
        for (size_t i = 0; i <= n; ++i) {
            if (i == n || txt[i] == ' ') {
                if (i > start) out.emplace_back(txt.substr(start, i - start));
                start = i + 1;
            }
        }
        return out;
    }

    if (txt.find(',') != string::npos) {
        vector<string> out;
        size_t start = 0;
        for (size_t i = 0; i <= n; ++i) {
            if (i == n || txt[i] == ',') {
                if (i > start) out.emplace_back(txt.substr(start, i - start));
                start = i + 1;
            }
        }
        return out;
    }

    int num = 0;
    for (size_t i = 0; i < n; ++i) {
        char c = txt[i];
        if (c >= 'a' && c <= 'z' && ((c & 1) == 0)) ++num;
    }

    return {to_string(num)};
}
