#include <string>

int count_upper(std::string s) {
    int count = 0;
    for (std::size_t i = 0, n = s.size(); i < n; i += 2) {
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
