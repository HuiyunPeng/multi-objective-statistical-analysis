#include <vector>
#include <string>
using namespace std;

vector<string> reverse_delete(string s, string c) {
    bool remove_chars[256] = {false};
    for (unsigned char ch : c) {
        remove_chars[ch] = true;
    }

    string n;
    n.reserve(s.size());
    for (unsigned char ch : s) {
        if (!remove_chars[ch]) {
            n.push_back(static_cast<char>(ch));
        }
    }

    bool is_palindrome = true;
    for (size_t i = 0, j = n.size(); i < j / 2; ++i) {
        if (n[i] != n[j - 1 - i]) {
            is_palindrome = false;
            break;
        }
    }

    return {n, is_palindrome ? "True" : "False"};
}
