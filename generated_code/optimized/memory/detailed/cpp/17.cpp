#include <vector>
#include <string>
using namespace std;

vector<int> parse_music(string music_string) {
    vector<int> out;
    const size_t n = music_string.size();
    size_t start = 0;

    while (start < n) {
        while (start < n && music_string[start] == ' ') ++start;
        if (start >= n) break;

        size_t end = start;
        while (end < n && music_string[end] != ' ') ++end;

        const size_t len = end - start;
        if (len == 1) {
            if (music_string[start] == 'o') out.push_back(4);
        } else if (len == 2) {
            const char a = music_string[start];
            const char b = music_string[start + 1];
            if (a == 'o' && b == '|') out.push_back(2);
            else if (a == '.' && b == '|') out.push_back(1);
        }

        start = end + 1;
    }

    return out;
}
