#include <string>
using namespace std;

int vowels_count(string s) {
    int count = 0;

    for (char c : s) {
        switch (c) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                ++count;
                break;
        }
    }

    if (!s.empty()) {
        char last = s.back();
        if (last == 'y' || last == 'Y') {
            ++count;
        }
    }

    return count;
}
