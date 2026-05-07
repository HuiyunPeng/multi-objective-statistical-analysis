#include <vector>
#include <string>
using namespace std;

vector<string> reverse_delete(string s, string c) {
    bool remove_chars[256] = {false};
    for (char ch : c) {
        remove_chars[(unsigned char)ch] = true;
    }

    string n;
    n.reserve(s.size());
    for (char ch : s) {
        if (!remove_chars[(unsigned char)ch]) {
            n.push_back(ch);
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
