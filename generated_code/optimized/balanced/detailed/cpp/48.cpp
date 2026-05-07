#include <string>
using namespace std;

bool is_palindrome(string text) {
    size_t i = 0;
    size_t j = text.size();
    if (j < 2) return true;

    --j;
    while (i < j) {
        if (text[i] != text[j]) return false;
        ++i;
        --j;
    }
    return true;
}
