#include <string>
using namespace std;

static inline bool is_ascii_letter(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool check_if_last_char_is_a_letter(string txt) {
    const size_t n = txt.size();
    if (n == 0) return false;

    const unsigned char last = static_cast<unsigned char>(txt[n - 1]);
    if (!is_ascii_letter(last)) return false;

    return n == 1 || !is_ascii_letter(static_cast<unsigned char>(txt[n - 2]));
}
