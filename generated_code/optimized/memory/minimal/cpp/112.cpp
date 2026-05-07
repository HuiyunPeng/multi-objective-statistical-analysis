#include <string>
#include <vector>
using namespace std;

vector<string> reverse_delete(string s, string c) {
    bool remove[256] = {false};
    for (unsigned char ch : c) {
        remove[ch] = true;
    }

    string n;
    n.reserve(s.size());
    for (unsigned char ch : s) {
        if (!remove[ch]) {
            n.push_back(static_cast<char>(ch));
        }
    }

    bool isPalindrome = true;
    for (size_t i = 0, j = n.size(); i < j / 2; ++i) {
        if (n[i] != n[j - 1 - i]) {
            isPalindrome = false;
            break;
        }
    }

    return {n, isPalindrome ? "True" : "False"};
}
