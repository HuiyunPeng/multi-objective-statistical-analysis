#include <string>
#include <vector>
using namespace std;

string words_in_sentence(string sentence) {
    const int n = static_cast<int>(sentence.size());
    vector<bool> isPrime(n + 1, true);
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                isPrime[multiple] = false;
            }
        }
    }

    string out;
    out.reserve(n);

    int start = 0;
    for (int i = 0; i <= n; ++i) {
        if (i == n || sentence[i] == ' ') {
            const int len = i - start;
            if (len > 1 && isPrime[len]) {
                out.append(sentence, start, len);
                out.push_back(' ');
            }
            start = i + 1;
        }
    }

    if (!out.empty()) out.pop_back();
    return out;
}
