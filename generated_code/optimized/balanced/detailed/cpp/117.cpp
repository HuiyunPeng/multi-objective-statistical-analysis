#include <vector>
#include <string>
using namespace std;

vector<string> select_words(string s, int n) {
    vector<string> out;
    if (n < 0) return out;

    string current;
    int numc = 0;
    const size_t len = s.size();

    for (size_t i = 0; i < len; ++i) {
        const char c = s[i];

        if (c == ' ') {
            if (numc == n) out.push_back(current);
            current.clear();
            numc = 0;
        } else {
            current.push_back(c);

            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                const char lower = static_cast<char>(c | 32);
                if (lower != 'a' && lower != 'e' && lower != 'i' && lower != 'o' && lower != 'u') {
                    ++numc;
                }
            }
        }
    }

    if (numc == n) out.push_back(current);
    return out;
}
