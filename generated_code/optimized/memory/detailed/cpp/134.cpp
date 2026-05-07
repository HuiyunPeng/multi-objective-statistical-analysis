#include <string>
using namespace std;

bool check_if_last_char_is_a_letter(string txt) {
    const size_t n = txt.size();
    if (n == 0) return false;

    const char last = txt[n - 1];
    if (!((last >= 'A' && last <= 'Z') || (last >= 'a' && last <= 'z'))) return false;
    if (n == 1) return true;

    const char prev = txt[n - 2];
    return !((prev >= 'A' && prev <= 'Z') || (prev >= 'a' && prev <= 'z'));
}
