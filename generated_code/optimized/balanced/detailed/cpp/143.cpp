#include <string>
#include <vector>
using namespace std;

string words_in_sentence(string sentence) {
    const size_t n = sentence.size();
    vector<signed char> prime(3, -1);
    prime[0] = 0;
    prime[1] = 0;
    prime[2] = 1;

    size_t write = 0;
    size_t i = 0;

    while (i < n) {
        while (i < n && sentence[i] == ' ') ++i;
        if (i >= n) break;

        const size_t start = i;
        while (i < n && sentence[i] != ' ') ++i;
        const size_t len = i - start;

        if (len >= prime.size()) prime.resize(len + 1, -1);

        signed char& is_prime = prime[len];
        if (is_prime == -1) {
            if (len < 2) {
                is_prime = 0;
            } else if ((len & 1u) == 0) {
                is_prime = (len == 2);
            } else {
                is_prime = 1;
                for (size_t d = 3; d <= len / d; d += 2) {
                    if (len % d == 0) {
                        is_prime = 0;
                        break;
                    }
                }
            }
        }

        if (is_prime) {
            if (write != 0) sentence[write++] = ' ';
            if (write != start) {
                for (size_t k = 0; k < len; ++k) {
                    sentence[write + k] = sentence[start + k];
                }
            }
            write += len;
        }
    }

    sentence.resize(write);
    return sentence;
}
