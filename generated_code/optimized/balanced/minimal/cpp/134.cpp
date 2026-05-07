#include <string>
using std::string;

bool check_if_last_char_is_a_letter(string txt) {
    const auto n = txt.size();
    if (n == 0) return false;

    const unsigned char last = static_cast<unsigned char>(txt[n - 1]);
    const unsigned char last_lower = static_cast<unsigned char>(last | 32);
    if (last_lower < 'a' || last_lower > 'z') return false;

    if (n == 1) return true;

    const unsigned char prev = static_cast<unsigned char>(txt[n - 2]);
    const unsigned char prev_lower = static_cast<unsigned char>(prev | 32);
    return prev_lower < 'a' || prev_lower > 'z';
}
