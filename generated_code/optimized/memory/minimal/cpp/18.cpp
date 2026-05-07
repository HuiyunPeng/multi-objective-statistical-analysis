#include <string>
using namespace std;

int how_many_times(string str, string substring) {
    const size_t n = str.size();
    const size_t m = substring.size();

    if (n == 0 || m == 0 || m > n) return 0;

    int out = 0;
    for (size_t i = 0; i + m <= n; ++i) {
        if (str.compare(i, m, substring) == 0) {
            ++out;
        }
    }
    return out;
}
