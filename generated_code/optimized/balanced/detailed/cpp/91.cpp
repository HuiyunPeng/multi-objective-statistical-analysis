#include <string>
using namespace std;

int is_bored(string S) {
    int sum = 0;
    bool isstart = true;
    const size_t n = S.size();

    for (size_t i = 0; i < n; ++i) {
        const char c = S[i];

        if (isstart && c == 'I' && i + 1 < n && S[i + 1] == ' ')
            ++sum;

        if (c != ' ')
            isstart = (c == '.' || c == '?' || c == '!');
    }

    return sum;
}
