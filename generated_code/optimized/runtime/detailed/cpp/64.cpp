#include <string>
using namespace std;

int vowels_count(string s) {
    int count = 0;
    const int n = static_cast<int>(s.size());

    for (int i = 0; i < n; ++i) {
        switch (s[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                ++count;
                break;
        }
    }

    if (n > 0 && (s[n - 1] == 'y' || s[n - 1] == 'Y')) {
        ++count;
    }

    return count;
}
