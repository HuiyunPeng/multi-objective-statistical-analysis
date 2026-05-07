#include <string>
#include <vector>

using namespace std;

vector<string> select_words(string s, int n) {
    vector<string> out;
    string current;
    int numc = 0;
    const size_t len = s.size();

    for (size_t i = 0; i <= len; ++i) {
        const char c = (i == len) ? ' ' : s[i];

        if (c == ' ') {
            if (numc == n) out.push_back(current);
            current.clear();
            numc = 0;
        } else {
            current.push_back(c);
            if ((c >= 'A' && c <= 'Z')) {
                switch (c) {
                    case 'A': case 'E': case 'I': case 'O': case 'U':
                        break;
                    default:
                        ++numc;
                }
            } else if ((c >= 'a' && c <= 'z')) {
                switch (c) {
                    case 'a': case 'e': case 'i': case 'o': case 'u':
                        break;
                    default:
                        ++numc;
                }
            }
        }
    }

    return out;
}
