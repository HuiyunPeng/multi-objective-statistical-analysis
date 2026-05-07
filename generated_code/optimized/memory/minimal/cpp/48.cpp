#include <string>
using namespace std;

bool is_palindrome(string text) {
    size_t i = 0, j = text.size();
    if (j == 0) return true;
    --j;
    while (i < j) {
        if (text[i] != text[j]) return false;
        ++i;
        --j;
    }
    return true;
}
