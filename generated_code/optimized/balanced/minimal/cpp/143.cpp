#include <string>
using namespace std;

string words_in_sentence(string sentence) {
    string out;
    out.reserve(sentence.size());

    const size_t n = sentence.size();
    size_t start = 0;
    bool in_word = false;

    for (size_t i = 0; i <= n; ++i) {
        if (i < n && sentence[i] != ' ') {
            if (!in_word) {
                start = i;
                in_word = true;
            }
        } else if (in_word) {
            const size_t len = i - start;
            bool is_prime = false;

            if (len == 2) {
                is_prime = true;
            } else if (len > 2 && (len & 1)) {
                is_prime = true;
                for (size_t d = 3; d <= len / d; d += 2) {
                    if (len % d == 0) {
                        is_prime = false;
                        break;
                    }
                }
            }

            if (is_prime) {
                if (!out.empty()) out.push_back(' ');
                out.append(sentence, start, len);
            }

            in_word = false;
        }
    }

    return out;
}
