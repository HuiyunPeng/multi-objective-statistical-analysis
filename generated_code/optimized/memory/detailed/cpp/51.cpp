#include <string>
using namespace std;

string remove_vowels(string text) {
    size_t write = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        switch (c) {
            case 'A': case 'E': case 'I': case 'O': case 'U':
            case 'a': case 'e': case 'i': case 'o': case 'u':
                break;
            default:
                text[write++] = c;
        }
    }
    text.resize(write);
    return text;
}
