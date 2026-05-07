#include <vector>
#include <string>

using namespace std;

vector<int> parse_music(string music_string) {
    vector<int> out;
    const size_t n = music_string.size();
    size_t start = string::npos;

    for (size_t i = 0; i <= n; ++i) {
        if (i == n || music_string[i] == ' ') {
            if (start != string::npos) {
                const size_t len = i - start;
                const char* s = music_string.data() + start;

                if (len == 1) {
                    if (s[0] == 'o') out.push_back(4);
                } else if (len == 2) {
                    if (s[0] == 'o' && s[1] == '|') out.push_back(2);
                    else if (s[0] == '.' && s[1] == '|') out.push_back(1);
                }

                start = string::npos;
            }
        } else if (start == string::npos) {
            start = i;
        }
    }

    return out;
}
