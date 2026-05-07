#include <string>
using namespace std;

bool is_palindrome(string str) {
    size_t left = 0, right = str.size();
    while (left < right) {
        if (str[left++] != str[--right]) {
            return false;
        }
    }
    return true;
}

string make_palindrome(string str) {
    const size_t n = str.size();

    for (size_t i = 0; i < n; ++i) {
        size_t left = i, right = n;
        bool palindrome = true;

        while (left < right) {
            if (str[left++] != str[--right]) {
                palindrome = false;
                break;
            }
        }

        if (palindrome) {
            str.reserve(n + i);
            for (size_t j = i; j > 0; --j) {
                str.push_back(str[j - 1]);
            }
            return str;
        }
    }

    str.reserve(n * 2);
    for (size_t j = n; j > 0; --j) {
        str.push_back(str[j - 1]);
    }
    return str;
}
