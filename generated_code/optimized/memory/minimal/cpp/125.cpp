#include <string>
#include <vector>
using namespace std;

vector<string> split_words(string txt) {
    char delim = 0;
    for (char c : txt) {
        if (c == ' ') {
            delim = ' ';
            break;
        }
        if (c == ',') {
            delim = ',';
        }
    }

    if (delim) {
        vector<string> out;
        string current;

        for (char c : txt) {
            if (c == delim) {
                if (!current.empty()) {
                    out.emplace_back();
                    out.back().swap(current);
                }
            } else {
                current.push_back(c);
            }
        }

        if (!current.empty()) {
            out.emplace_back();
            out.back().swap(current);
        }

        return out;
    }

    int num = 0;
    for (unsigned char c : txt) {
        if (c >= 'a' && c <= 'z' && (c % 2 == 0)) {
            ++num;
        }
    }

    return vector<string>{to_string(num)};
}
