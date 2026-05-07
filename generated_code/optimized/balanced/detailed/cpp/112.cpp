#include <string>
#include <vector>
using namespace std;

vector<string> reverse_delete(string s, string c) {
    bool to_remove[256] = {false};
    for (unsigned char ch : c) {
        to_remove[ch] = true;
    }

    string n;
    n.reserve(s.size());
    for (unsigned char ch : s) {
        if (!to_remove[ch]) {
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

    vector<string> result;
    result.reserve(2);
    result.emplace_back(std::move(n));
    result.emplace_back(is_palindrome ? "True" : "False");
    return result;
}
