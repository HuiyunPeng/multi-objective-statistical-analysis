#include <vector>
#include <string>

using namespace std;

vector<int> parse_music(string music_string) {
    vector<int> out;
    const size_t n = music_string.size();
    if (n == 0) return out;

    const char* s = music_string.data();
    size_t i = 0;

    while (i < n) {
        while (i < n && s[i] == ' ') ++i;
        if (i >= n) break;

        const size_t start = i;
        while (i < n && s[i] != ' ') ++i;
        const size_t len = i - start;

        if (len == 1) {
            if (s[start] == 'o') out.push_back(4);
        } else if (len == 2) {
            const char a = s[start];
            const char b = s[start + 1];
            if (a == 'o' && b == '|') out.push_back(2);
            else if (a == '.' && b == '|') out.push_back(1);
        }
    }

    return out;
}
