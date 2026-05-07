#include <string>
using namespace std;

bool same_chars(string s0, string s1) {
    unsigned long long mask0[4] = {0, 0, 0, 0};
    unsigned long long mask1[4] = {0, 0, 0, 0};

    for (unsigned char c : s0)
        mask0[c >> 6] |= 1ULL << (c & 63);

    for (unsigned char c : s1)
        mask1[c >> 6] |= 1ULL << (c & 63);

    return mask0[0] == mask1[0] &&
           mask0[1] == mask1[1] &&
           mask0[2] == mask1[2] &&
           mask0[3] == mask1[3];
}
