#include <string>
using namespace std;

bool check_if_last_char_is_a_letter(string txt) {
    size_t n = txt.size();
    if (n == 0) return false;

    char c = txt[n - 1];
    bool is_letter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    if (!is_letter) return false;

    if (n == 1) return true;

    c = txt[n - 2];
    return !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
