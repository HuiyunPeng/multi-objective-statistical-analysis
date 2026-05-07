#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <cstdint>

using namespace std;

bool cycpattern_check(string a, string b) {
    const size_t n = a.size();
    const size_t m = b.size();

    if (m == 0 || n < m) return false;

    string doubled = b;
    doubled += b;

    const char* ad = a.data();
    const char* dd = doubled.data();

    const uint64_t B = 1315423911ULL;
    uint64_t pow_m = 1;
    for (size_t i = 0; i < m; ++i) {
        pow_m *= B;
    }

    unordered_map<uint64_t, int> heads;
    heads.reserve(m);

    vector<int> next_idx(m, -1);

    uint64_t h = 0;
    for (size_t i = 0; i < m; ++i) {
        h = h * B + static_cast<uint64_t>(static_cast<unsigned char>(dd[i])) + 1ULL;
    }

    heads.emplace(h, 0);

    for (size_t start = 1; start < m; ++start) {
        h = h * B
          + static_cast<uint64_t>(static_cast<unsigned char>(dd[start + m - 1])) + 1ULL
          - (static_cast<uint64_t>(static_cast<unsigned char>(dd[start - 1])) + 1ULL) * pow_m;

        auto it = heads.find(h);
        if (it == heads.end()) {
            heads.emplace(h, static_cast<int>(start));
        } else {
            next_idx[start] = it->second;
            it->second = static_cast<int>(start);
        }
    }

    auto matches_rotation = [&](size_t a_start, uint64_t hash_value) -> bool {
        auto it = heads.find(hash_value);
        if (it == heads.end()) return false;

        for (int idx = it->second; idx != -1; idx = next_idx[idx]) {
            if (memcmp(ad + a_start, dd + idx, m) == 0) return true;
        }
        return false;
    };

    uint64_t ah = 0;
    for (size_t i = 0; i < m; ++i) {
        ah = ah * B + static_cast<uint64_t>(static_cast<unsigned char>(ad[i])) + 1ULL;
    }

    if (matches_rotation(0, ah)) return true;

    for (size_t start = 1; start <= n - m; ++start) {
        ah = ah * B
           + static_cast<uint64_t>(static_cast<unsigned char>(ad[start + m - 1])) + 1ULL
           - (static_cast<uint64_t>(static_cast<unsigned char>(ad[start - 1])) + 1ULL) * pow_m;

        if (matches_rotation(start, ah)) return true;
    }

    return false;
}
