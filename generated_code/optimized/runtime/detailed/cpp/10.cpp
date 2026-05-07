#include <string>
#include <vector>

using namespace std;

bool is_palindrome(string str) {
    size_t i = 0, j = str.size();
    while (i < j) {
        if (str[i] != str[j - 1]) return false;
        ++i;
        --j;
    }
    return true;
}

string make_palindrome(string str) {
    const size_t n = str.size();
    if (n < 2) return str;

    string rev(str.rbegin(), str.rend());

    vector<int> seq;
    seq.reserve(n * 2 + 1);
    for (char c : rev) seq.push_back(static_cast<unsigned char>(c));
    seq.push_back(256);
    for (char c : str) seq.push_back(static_cast<unsigned char>(c));

    vector<size_t> pi(seq.size(), 0);
    for (size_t i = 1; i < seq.size(); ++i) {
        size_t j = pi[i - 1];
        while (j > 0 && seq[i] != seq[j]) j = pi[j - 1];
        if (seq[i] == seq[j]) ++j;
        pi[i] = j;
    }

    const size_t palSuffixLen = pi.back();

    string result = str;
    result.reserve(n + (n - palSuffixLen));
    result.append(rev, palSuffixLen, n - palSuffixLen);
    return result;
}
