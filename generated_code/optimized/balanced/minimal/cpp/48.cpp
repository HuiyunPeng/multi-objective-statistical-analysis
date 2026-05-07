#include <string>

bool is_palindrome(std::string text) {
    size_t i = 0, j = text.size();
    while (i < j) {
        if (text[i] != text[j - 1]) return false;
        ++i;
        --j;
    }
    return true;
}
