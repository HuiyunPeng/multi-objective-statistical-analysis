#include <string>
using namespace std;

bool is_palindrome(string str) {
    size_t left = 0, right = str.size();
    if (right == 0) return true;
    --right;
    while (left < right) {
        if (str[left++] != str[right--]) return false;
    }
    return true;
}

string make_palindrome(string str) {
    const size_t n = str.size();
    size_t i = 0;

    for (; i < n; ++i) {
        size_t left = i, right = n;
        --right;
        bool ok = true;

        while (left < right) {
            if (str[left++] != str[right--]) {
                ok = false;
                break;
            }
        }

        if (ok) break;
    }

    string result;
    result.reserve(n + i);
    result = str;

    while (i > 0) {
        result += str[--i];
    }

    return result;
}
