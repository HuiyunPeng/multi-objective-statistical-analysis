#include <string>
#include <vector>
using namespace std;

vector<string> split_words(string txt) {
    char sep = 0;
    for (char c : txt) {
        if (c == ' ') {
            sep = ' ';
            break;
        }
    }
    if (!sep) {
        for (char c : txt) {
            if (c == ',') {
                sep = ',';
                break;
            }
        }
    }

    if (sep) {
        vector<string> out;
        const size_t n = txt.size();
        size_t start = 0;

        for (size_t i = 0; i <= n; ++i) {
            if (i == n || txt[i] == sep) {
                if (i > start) {
                    out.emplace_back(txt.data() + start, i - start);
                }
                start = i + 1;
            }
        }
        return out;
    }

    int num = 0;
    for (unsigned char c : txt) {
        if (c >= 'a' && c <= 'z' && (c % 2 == 0)) {
            ++num;
        }
    }

    return {to_string(num)};
}
