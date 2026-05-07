#include <string>
using namespace std;

bool same_chars(string s0, string s1) {
    unsigned char marks[256] = {};

    for (char c : s0)
        marks[(unsigned char)c] |= 1;

    for (char c : s1)
        marks[(unsigned char)c] |= 2;

    for (int i = 0; i < 256; ++i)
        if (marks[i] == 1 || marks[i] == 2)
            return false;

    return true;
}
