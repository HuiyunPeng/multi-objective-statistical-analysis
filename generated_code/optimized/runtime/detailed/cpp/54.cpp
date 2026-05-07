#include <string>
using namespace std;

bool same_chars(string s0, string s1) {
    if (s0.size() == s1.size() && s0 == s1) return true;

    bool present0[256] = {false};
    bool present1[256] = {false};

    for (unsigned char c : s0) present0[c] = true;
    for (unsigned char c : s1) present1[c] = true;

    for (int i = 0; i < 256; ++i) {
        if (present0[i] != present1[i]) return false;
    }
    return true;
}
