#include <vector>
#include <string>

using namespace std;

vector<int> parse_music(string music_string) {
    vector<int> out;
    const size_t n = music_string.size();

    size_t tokens = 0;
    bool in_token = false;
    for (size_t i = 0; i < n; ++i) {
        if (music_string[i] == ' ') {
            if (in_token) {
                ++tokens;
                in_token = false;
            }
        } else {
            in_token = true;
        }
    }
    if (in_token) ++tokens;
    out.reserve(tokens);

    size_t i = 0;
    while (i < n) {
        while (i < n && music_string[i] == ' ') ++i;
        if (i >= n) break;

        const size_t start = i;
        while (i < n && music_string[i] != ' ') ++i;
        const size_t len = i - start;

        if (len == 1) {
            if (music_string[start] == 'o') out.push_back(4);
        } else if (len == 2) {
            if (music_string[start] == 'o' && music_string[start + 1] == '|') out.push_back(2);
            else if (music_string[start] == '.' && music_string[start + 1] == '|') out.push_back(1);
        }
    }

    return out;
}
