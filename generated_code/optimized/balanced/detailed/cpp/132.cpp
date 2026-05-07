#include <string>

bool is_nested(std::string str) {
    int count = 0;
    int maxcount = 0;

    for (char c : str) {
        if (c == '[') {
            ++count;
        } else if (c == ']') {
            --count;
            if (count < 0) count = 0;
        }

        if (count > maxcount) {
            maxcount = count;
        } else if (count <= maxcount - 2) {
            return true;
        }
    }

    return false;
}
