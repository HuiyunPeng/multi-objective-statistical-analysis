#include <string>
using std::string;

bool is_nested(string str) {
    int depth = 0;
    int max_depth = 0;

    const char* p = str.data();
    const char* end = p + str.size();

    for (; p != end; ++p) {
        if (*p == '[') {
            if (++depth > max_depth) max_depth = depth;
        } else if (*p == ']') {
            if (--depth < 0) depth = 0;
            if (depth <= max_depth - 2) return true;
        }
    }

    return false;
}
