#include <string>
using namespace std;

int how_many_times(string str, string substring) {
    const size_t n = str.size();
    const size_t m = substring.size();

    if (n == 0) return 0;
    if (m == 0) return static_cast<int>(n + 1);
    if (m > n) return 0;

    int count = 0;
    size_t pos = 0;

    while (true) {
        pos = str.find(substring, pos);
        if (pos == string::npos) break;
        ++count;
        ++pos; // allow overlapping matches
    }

    return count;
}
