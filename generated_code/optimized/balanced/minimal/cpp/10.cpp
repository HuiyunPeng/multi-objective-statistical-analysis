#include <string>
#include <vector>

using namespace std;

bool is_palindrome(string str) {
    size_t l = 0, r = str.size();
    while (l < r) {
        if (str[l] != str[r - 1]) return false;
        ++l;
        --r;
    }
    return true;
}

string make_palindrome(string str) {
    const size_t n = str.size();
    if (n < 2) return str;

    const size_t m = 2 * n + 1;
    vector<size_t> pi(m, 0);

    auto get_char = [&](size_t idx) -> unsigned int {
        if (idx < n) return static_cast<unsigned char>(str[n - 1 - idx]);
        if (idx == n) return 256u; // unique separator outside unsigned char range
        return static_cast<unsigned char>(str[idx - n - 1]);
    };

    for (size_t i = 1; i < m; ++i) {
        size_t j = pi[i - 1];
        const unsigned int ci = get_char(i);
        while (j > 0 && ci != get_char(j)) j = pi[j - 1];
        if (ci == get_char(j)) ++j;
        pi[i] = j;
    }

    const size_t pal_suffix_len = pi[m - 1];
    str.reserve(2 * n - pal_suffix_len);
    for (size_t i = n - pal_suffix_len; i > 0; --i) {
        str.push_back(str[i - 1]);
    }
    return str;
}
