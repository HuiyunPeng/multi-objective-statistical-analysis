#include <string>
using namespace std;

string get_closest_vowel(string word) {
    const int n = static_cast<int>(word.size());
    if (n < 3) return string();

    auto is_vowel = [](char c) {
        switch (c) {
            case 'A': case 'E': case 'I': case 'O': case 'U':
            case 'a': case 'e': case 'i': case 'o': case 'u':
                return true;
            default:
                return false;
        }
    };

    for (int i = n - 2; i >= 1; --i) {
        if (is_vowel(word[i]) && !is_vowel(word[i - 1]) && !is_vowel(word[i + 1])) {
            return string(1, word[i]);
        }
    }

    return string();
}
