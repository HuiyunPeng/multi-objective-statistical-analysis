#include <vector>
#include <string>
using namespace std;

vector<int> parse_music(string music_string) {
    vector<int> out;
    const size_t n = music_string.size();
    out.reserve((n + 1) >> 1);

    size_t i = 0;
    while (i < n) {
        while (i < n && music_string[i] == ' ') ++i;
        if (i >= n) break;

        size_t j = i;
        while (j < n && music_string[j] != ' ') ++j;

        const size_t len = j - i;
        if (len == 1) {
            if (music_string[i] == 'o') out.push_back(4);
        } else if (len == 2) {
            const char a = music_string[i];
            const char b = music_string[i + 1];
            if (a == 'o' && b == '|') out.push_back(2);
            else if (a == '.' && b == '|') out.push_back(1);
        }

        i = j + 1;
    }

    return out;
}
