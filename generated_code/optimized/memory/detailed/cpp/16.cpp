#include <string>
#include <cctype>
using namespace std;

int count_distinct_characters(string str) {
    bool seen[256] = {false};
    int count = 0;

    for (char c : str) {
        unsigned char uc = static_cast<unsigned char>(c);
        uc = static_cast<unsigned char>(tolower(uc));
        if (!seen[uc]) {
            seen[uc] = true;
            ++count;
        }
    }

    return count;
}
