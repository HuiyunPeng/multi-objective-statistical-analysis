#include <string>

using namespace std;

string fix_spaces(string text) {
    string out;
    out.reserve(text.size());

    int spacelen = 0;
    const size_t n = text.size();

    for (size_t i = 0; i < n; ++i) {
        char c = text[i];
        if (c == ' ') {
            ++spacelen;
        } else {
            if (spacelen == 1) {
                out.push_back('_');
            } else if (spacelen == 2) {
                out.append("__");
            } else if (spacelen > 2) {
                out.push_back('-');
            }
            spacelen = 0;
            out.push_back(c);
        }
    }

    if (spacelen == 1) {
        out.push_back('_');
    } else if (spacelen == 2) {
        out.append("__");
    } else if (spacelen > 2) {
        out.push_back('-');
    }

    return out;
}
