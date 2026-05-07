#include <string>
#include <vector>

using namespace std;

vector<string> split_words(string txt) {
    size_t space_count = 0, comma_count = 0;
    int num = 0;

    for (unsigned char c : txt) {
        if (c == ' ') {
            ++space_count;
        } else if (c == ',') {
            ++comma_count;
        } else if (c >= 'a' && c <= 'z' && ((c & 1u) == 0)) {
            ++num;
        }
    }

    if (space_count) {
        vector<string> out;
        out.reserve(space_count + 1);
        const size_t n = txt.size();
        size_t start = 0;

        for (size_t i = 0; i <= n; ++i) {
            if (i == n || txt[i] == ' ') {
                if (i > start) out.emplace_back(txt, start, i - start);
                start = i + 1;
            }
        }
        return out;
    }

    if (comma_count) {
        vector<string> out;
        out.reserve(comma_count + 1);
        const size_t n = txt.size();
        size_t start = 0;

        for (size_t i = 0; i <= n; ++i) {
            if (i == n || txt[i] == ',') {
                if (i > start) out.emplace_back(txt, start, i - start);
                start = i + 1;
            }
        }
        return out;
    }

    return {to_string(num)};
}
