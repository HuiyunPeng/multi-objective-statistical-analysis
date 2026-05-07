#include <string>
using namespace std;

int how_many_times(string str, string substring) {
    if (str.empty()) return 0;

    const size_t subLen = substring.size();
    if (subLen == 0) return static_cast<int>(str.size() + 1);
    if (subLen > str.size()) return 0;

    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(substring, pos)) != string::npos) {
        ++count;
        ++pos; // allow overlapping matches
    }
    return count;
}
