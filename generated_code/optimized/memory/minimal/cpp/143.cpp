#include <string>
using namespace std;

string words_in_sentence(string sentence) {
    string out;
    const size_t n = sentence.size();
    size_t i = 0;

    while (i < n) {
        while (i < n && sentence[i] == ' ') ++i;
        if (i >= n) break;

        size_t start = i;
        while (i < n && sentence[i] != ' ') ++i;
        size_t len = i - start;

        bool isp = len >= 2;
        for (size_t j = 2; isp && j * j <= len; ++j) {
            if (len % j == 0) isp = false;
        }

        if (isp) {
            if (!out.empty()) out.push_back(' ');
            out.append(sentence, start, len);
        }
    }

    return out;
}
