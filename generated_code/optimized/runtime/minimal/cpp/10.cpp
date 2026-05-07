#include <string>
#include <vector>
using namespace std;

bool is_palindrome(string str) {
    int l = 0, r = (int)str.size() - 1;
    while (l < r) {
        if (str[l++] != str[r--]) return false;
    }
    return true;
}

string make_palindrome(string str) {
    int n = (int)str.size();
    if (n <= 1) return str;

    int best = 1;

    // Manacher's algorithm for odd-length palindromes
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && str[i - k] == str[i + k]) ++k;
        d1[i] = k;
        int end = i + k - 1;
        if (end == n - 1) {
            int len = 2 * k - 1;
            if (len > best) best = len;
        }
        --k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    // Manacher's algorithm for even-length palindromes
    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && str[i - k - 1] == str[i + k]) ++k;
        d2[i] = k;
        int end = i + k - 1;
        if (end == n - 1) {
            int len = 2 * k;
            if (len > best) best = len;
        }
        --k;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    string result;
    result.reserve(2 * n - best);
    result = str;
    for (int i = n - best - 1; i >= 0; --i) {
        result.push_back(str[i]);
    }
    return result;
}
