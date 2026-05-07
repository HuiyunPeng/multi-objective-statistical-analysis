#include <vector>
#include <string>
using namespace std;

vector<int> parse_music(string music_string) {
    vector<int> out;
    const int n = (int)music_string.size();
    if (n == 0) return out;

    out.reserve((n + 1) / 2);

    int i = 0;
    while (i < n) {
        while (i < n && music_string[i] == ' ') ++i;
        if (i >= n) break;

        const int start = i;
        while (i < n && music_string[i] != ' ') ++i;
        const int len = i - start;

        if (len == 1) {
            if (music_string[start] == 'o') out.push_back(4);
        } else if (len == 2) {
            const char a = music_string[start];
            const char b = music_string[start + 1];
            if (a == 'o' && b == '|') out.push_back(2);
            else if (a == '.' && b == '|') out.push_back(1);
        }
    }

    return out;
}
