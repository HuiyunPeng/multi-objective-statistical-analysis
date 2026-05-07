#include <string>
#include <cstdint>

bool same_chars(std::string s0, std::string s1) {
    uint64_t mask0[4] = {0, 0, 0, 0};
    uint64_t mask1[4] = {0, 0, 0, 0};

    for (unsigned char c : s0)
        mask0[c >> 6] |= 1ULL << (c & 63);

    for (unsigned char c : s1)
        mask1[c >> 6] |= 1ULL << (c & 63);

    return mask0[0] == mask1[0] &&
           mask0[1] == mask1[1] &&
           mask0[2] == mask1[2] &&
           mask0[3] == mask1[3];
}
