#include <string>

std::string remove_vowels(std::string text) {
    std::size_t write = 0;

    for (std::size_t read = 0, n = text.size(); read < n; ++read) {
        const char c = text[read];
        switch (c) {
            case 'A': case 'E': case 'I': case 'O': case 'U':
            case 'a': case 'e': case 'i': case 'o': case 'u':
                break;
            default:
                text[write++] = c;
                break;
        }
    }

    text.resize(write);
    return text;
}
