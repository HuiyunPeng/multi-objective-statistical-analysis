#include <string>
#include <cctype>

using namespace std;

int count_distinct_characters(string str) {
    bool seen[256] = {false};
    int count = 0;

    for (char ch : str) {
        unsigned char c = static_cast<unsigned char>(ch);
        c = static_cast<unsigned char>(tolower(c));
        if (!seen[c]) {
            seen[c] = true;
            ++count;
        }
    }

    return count;
}
