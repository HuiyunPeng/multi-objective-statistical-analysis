#include <string>
using std::string;

int is_bored(string S) {
    bool is_start = true;
    bool pending_i = false;
    int sum = 0;

    for (char c : S) {
        if (pending_i && c == ' ') {
            ++sum;
        }

        pending_i = is_start && c == 'I';

        if (c != ' ') {
            is_start = false;
        }
        if (c == '.' || c == '?' || c == '!') {
            is_start = true;
        }
    }

    return sum;
}
