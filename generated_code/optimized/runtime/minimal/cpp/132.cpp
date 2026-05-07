#include <string>
using namespace std;

bool is_nested(string str) {
    int count = 0;
    int threshold = -2;
    const char* p = str.data();
    const char* end = p + str.size();

    for (; p != end; ++p) {
        if (*p == '[') {
            ++count;
        } else if (*p == ']') {
            --count;
        }

        if (count < 0) {
            count = 0;
        }

        if (count > threshold + 2) {
            threshold = count - 2;
        } else if (count <= threshold) {
            return true;
        }
    }

    return false;
}
