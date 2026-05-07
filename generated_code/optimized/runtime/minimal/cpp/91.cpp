#include <string>
using namespace std;

int is_bored(string S) {
    const char* p = S.data();
    const size_t n = S.size();
    bool atStart = true;
    int sum = 0;

    for (size_t i = 0; i < n; ++i) {
        const char c = p[i];

        if (atStart) {
            if (c == ' ') continue;
            if (c == 'I' && i + 1 < n && p[i + 1] == ' ') ++sum;
            atStart = (c == '.' || c == '?' || c == '!');
        } else if (c == '.' || c == '?' || c == '!') {
            atStart = true;
        }
    }

    return sum;
}
