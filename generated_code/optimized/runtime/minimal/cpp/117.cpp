#include <vector>
#include <string>
using namespace std;

vector<string> select_words(string s, int n) {
    vector<string> out;
    int numc = 0;
    size_t start = 0;
    const size_t len = s.size();

    for (size_t i = 0; i <= len; ++i) {
        if (i == len || s[i] == ' ') {
            if (numc == n) out.emplace_back(s.substr(start, i - start));
            start = i + 1;
            numc = 0;
        } else {
            unsigned char c = static_cast<unsigned char>(s[i]);
            unsigned char lower = static_cast<unsigned char>(c | 32);
            if (lower >= 'a' && lower <= 'z' &&
                lower != 'a' && lower != 'e' && lower != 'i' && lower != 'o' && lower != 'u') {
                ++numc;
            }
        }
    }

    return out;
}
