#include <string>
using namespace std;

int vowels_count(string s) {
    const size_t n = s.size();
    if (n == 0) return 0;

    int count = 0;
    for (size_t i = 0; i < n; ++i) {
        switch (s[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                ++count;
                break;
        }
    }

    const char last = s[n - 1];
    if (last == 'y' || last == 'Y') ++count;

    return count;
}
