#include <string>
#include <bitset>
#include <cctype>
using namespace std;

int count_distinct_characters(string str) {
    bitset<256> seen;
    int count = 0;

    for (char ch : str) {
        unsigned char lower = static_cast<unsigned char>(
            tolower(static_cast<unsigned char>(ch))
        );
        if (!seen[lower]) {
            seen.set(lower);
            ++count;
        }
    }

    return count;
}
