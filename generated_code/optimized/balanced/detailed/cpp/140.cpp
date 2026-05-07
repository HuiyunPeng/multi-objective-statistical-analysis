#include <string>
using namespace std;

string fix_spaces(string text) {
    size_t write = 0;
    int spaces = 0;
    const size_t n = text.size();

    for (size_t read = 0; read < n; ++read) {
        const char c = text[read];
        if (c == ' ') {
            ++spaces;
        } else {
            if (spaces == 1) {
                text[write++] = '_';
            } else if (spaces == 2) {
                text[write++] = '_';
                text[write++] = '_';
            } else if (spaces > 2) {
                text[write++] = '-';
            }
            spaces = 0;
            text[write++] = c;
        }
    }

    if (spaces == 1) {
        text[write++] = '_';
    } else if (spaces == 2) {
        text[write++] = '_';
        text[write++] = '_';
    } else if (spaces > 2) {
        text[write++] = '-';
    }

    text.resize(write);
    return text;
}
