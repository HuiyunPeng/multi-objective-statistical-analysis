#include <string>
using namespace std;

string remove_vowels(string text) {
    string out;
    out.reserve(text.size());

    for (char c : text) {
        switch (c) {
            case 'A': case 'E': case 'I': case 'O': case 'U':
            case 'a': case 'e': case 'i': case 'o': case 'u':
                break;
            default:
                out.push_back(c);
        }
    }

    return out;
}
