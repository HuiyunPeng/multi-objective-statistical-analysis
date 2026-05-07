#include <string>
using namespace std;

string fix_spaces(string text) {
    size_t write = 0;
    size_t i = 0;
    const size_t n = text.size();

    while (i < n) {
        if (text[i] == ' ') {
            size_t start = i;
            while (i < n && text[i] == ' ') ++i;
            size_t spaces = i - start;

            if (spaces == 1) {
                text[write++] = '_';
            } else if (spaces == 2) {
                text[write++] = '_';
                text[write++] = '_';
            } else {
                text[write++] = '-';
            }
        } else {
            text[write++] = text[i++];
        }
    }

    text.resize(write);
    return text;
}
