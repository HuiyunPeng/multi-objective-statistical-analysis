#include <string>
using namespace std;

static inline bool is_ascii_letter(unsigned char c) {
    return static_cast<unsigned>(c - 'A') < 26u ||
           static_cast<unsigned>(c - 'a') < 26u;
}

bool check_if_last_char_is_a_letter(string txt) {
    const size_t len = txt.size();
    if (len == 0) return false;

    if (!is_ascii_letter(static_cast<unsigned char>(txt[len - 1]))) return false;
    if (len == 1) return true;

    return !is_ascii_letter(static_cast<unsigned char>(txt[len - 2]));
}
