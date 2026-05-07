#include <string>
#include <vector>
using namespace std;

vector<string> select_words(string s, int n) {
    vector<string> out;
    size_t start = 0;
    int numc = 0;
    const size_t len = s.size();

    for (size_t i = 0; i <= len; ++i) {
        char c = (i == len) ? ' ' : s[i];

        if (c == ' ') {
            if (numc == n) {
                out.emplace_back(s, start, i - start);
            }
            start = i + 1;
            numc = 0;
        } else {
            char lower = static_cast<char>(c | 32);
            if (lower >= 'a' && lower <= 'z' &&
                lower != 'a' && lower != 'e' && lower != 'i' &&
                lower != 'o' && lower != 'u') {
                ++numc;
            }
        }
    }

    return out;
}
