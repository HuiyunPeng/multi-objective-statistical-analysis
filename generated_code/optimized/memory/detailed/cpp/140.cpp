#include <stdio.h>
#include <string>
using namespace std;
#include <algorithm>
#include <math.h>
#include <stdlib.h>

string fix_spaces(string text) {
    size_t write = 0;
    int spacelen = 0;
    const size_t n = text.size();

    for (size_t read = 0; read < n; ++read) {
        if (text[read] == ' ') {
            ++spacelen;
        } else {
            if (spacelen == 1) {
                text[write++] = '_';
            } else if (spacelen == 2) {
                text[write++] = '_';
                text[write++] = '_';
            } else if (spacelen > 2) {
                text[write++] = '-';
            }
            spacelen = 0;
            text[write++] = text[read];
        }
    }

    if (spacelen == 1) {
        text[write++] = '_';
    } else if (spacelen == 2) {
        text[write++] = '_';
        text[write++] = '_';
    } else if (spacelen > 2) {
        text[write++] = '-';
    }

    text.resize(write);
    return text;
}
