#include <string>
using std::string;

static inline bool is_ascii_letter(unsigned char c) {
    return (c - 'A' <= 'Z' - 'A') || (c - 'a' <= 'z' - 'a');
}

bool check_if_last_char_is_a_letter(string txt) {
    const size_t n = txt.size();
    if (n == 0) return false;

    if (!is_ascii_letter(static_cast<unsigned char>(txt[n - 1]))) return false;
    if (n == 1) return true;

    return !is_ascii_letter(static_cast<unsigned char>(txt[n - 2]));
}
