#include <string>
using std::string;

string remove_vowels(string text) {
    size_t write = 0;
    for (size_t read = 0, n = text.size(); read < n; ++read) {
        switch (text[read]) {
            case 'A': case 'E': case 'I': case 'O': case 'U':
            case 'a': case 'e': case 'i': case 'o': case 'u':
                break;
            default:
                text[write++] = text[read];
        }
    }
    text.resize(write);
    return text;
}
