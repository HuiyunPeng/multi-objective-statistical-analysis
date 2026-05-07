#include <string>
#include <vector>
using namespace std;

string words_in_sentence(string sentence) {
    const int n = (int)sentence.size();
    vector<bool> isPrime(n + 1, true);
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    string out;
    out.reserve(n);

    int start = -1;
    for (int i = 0; i <= n; ++i) {
        if (i < n && sentence[i] != ' ') {
            if (start == -1) start = i;
        } else if (start != -1) {
            int len = i - start;
            if (isPrime[len]) {
                if (!out.empty()) out.push_back(' ');
                out.append(sentence, start, len);
            }
            start = -1;
        }
    }

    return out;
}
