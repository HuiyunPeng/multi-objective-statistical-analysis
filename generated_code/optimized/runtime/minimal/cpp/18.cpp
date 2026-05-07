#include <string>
#include <vector>
using namespace std;

int how_many_times(string str, string substring) {
    const size_t n = str.size();
    const size_t m = substring.size();

    if (n == 0) return 0;
    if (m == 0) return static_cast<int>(n + 1);
    if (m > n) return 0;

    vector<size_t> pi(m, 0);
    for (size_t i = 1, j = 0; i < m; ++i) {
        while (j > 0 && substring[i] != substring[j]) {
            j = pi[j - 1];
        }
        if (substring[i] == substring[j]) {
            ++j;
        }
        pi[i] = j;
    }

    int count = 0;
    for (size_t i = 0, j = 0; i < n; ++i) {
        while (j > 0 && str[i] != substring[j]) {
            j = pi[j - 1];
        }
        if (str[i] == substring[j]) {
            ++j;
        }
        if (j == m) {
            ++count;
            j = pi[j - 1];
        }
    }

    return count;
}
