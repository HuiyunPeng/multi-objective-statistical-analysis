#include <string>
using namespace std;

bool is_palindrome(string text) {
    size_t i = 0, j = text.size();
    while (i < j) {
        if (text[i++] != text[--j]) return false;
    }
    return true;
}
