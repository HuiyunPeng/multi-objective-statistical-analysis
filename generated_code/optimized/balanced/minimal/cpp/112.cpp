#include <string>
#include <vector>
using namespace std;

vector<string> reverse_delete(string s, string c) {
    bool remove[256] = {};
    for (char ch : c) {
        remove[(unsigned char)ch] = true;
    }

    string n;
    n.reserve(s.size());
    for (char ch : s) {
        if (!remove[(unsigned char)ch]) {
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

    vector<string> result;
    result.reserve(2);
    result.push_back(std::move(n));
    result.emplace_back(is_palindrome ? "True" : "False");
    return result;
}
