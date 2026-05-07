#include <string>
using std::string;

int count_upper(string s) {
    int count = 0;
    const size_t len = s.size();

    for (size_t i = 0; i < len; i += 2) {
        switch (s[i]) {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                ++count;
                break;
        }
    }

    return count;
}
