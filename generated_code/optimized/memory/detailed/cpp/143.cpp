#include <string>
using namespace std;

string words_in_sentence(string sentence) {
    string out;
    const size_t n = sentence.size();
    size_t start = 0;

    while (start < n) {
        while (start < n && sentence[start] == ' ') ++start;
        if (start >= n) break;

        size_t end = start;
        while (end < n && sentence[end] != ' ') ++end;

        const size_t len = end - start;
        bool isp = len >= 2;

        if (isp) {
            for (size_t j = 2; j * j <= len; ++j) {
                if (len % j == 0) {
                    isp = false;
                    break;
                }
            }
        }

        if (isp) {
            if (!out.empty()) out += ' ';
            out.append(sentence, start, len);
        }

        start = end + 1;
    }

    return out;
}
