#include <string>
#include <cctype>

using namespace std;

int count_distinct_characters(string str) {
    bool seen[256] = {};
    int count = 0;

    for (unsigned char ch : str) {
        ch = static_cast<unsigned char>(tolower(ch));
        if (!seen[ch]) {
            seen[ch] = true;
            ++count;
        }
    }

    return count;
}
