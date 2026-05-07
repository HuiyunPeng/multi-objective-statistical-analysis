#include <string>
#include <vector>
using namespace std;

vector<string> select_words(string s, int n) {
    vector<string> out;
    const size_t len = s.size();
    size_t start = 0;
    int numc = 0;

    for (size_t i = 0; i <= len; ++i) {
        const char c = (i == len) ? ' ' : s[i];

        if (c == ' ') {
            if (numc == n) {
                out.emplace_back(s, start, i - start);
            }
            start = i + 1;
            numc = 0;
        } else {
            const unsigned char uc = static_cast<unsigned char>(c);
            const unsigned char lc = static_cast<unsigned char>(uc | 32);
            if (lc >= 'a' && lc <= 'z' &&
                lc != 'a' && lc != 'e' && lc != 'i' && lc != 'o' && lc != 'u') {
                ++numc;
            }
        }
    }

    return out;
}
