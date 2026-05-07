#include <string>
#include <cctype>
using namespace std;

int count_distinct_characters(string str) {
    bool seen[256] = {false};
    int count = 0;

    for (unsigned char c : str) {
        unsigned char lc = static_cast<unsigned char>(tolower(c));
        if (!seen[lc]) {
            seen[lc] = true;
            ++count;
        }
    }

    return count;
}
