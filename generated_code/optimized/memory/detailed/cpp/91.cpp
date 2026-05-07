#include <string>

using std::string;

int is_bored(string S) {
    bool is_start = true;
    bool saw_starting_i = false;
    int sum = 0;

    for (char c : S) {
        if (c == ' ' && saw_starting_i) {
            ++sum;
        }

        saw_starting_i = (c == 'I' && is_start);

        if (c != ' ') {
            is_start = false;
        }
        if (c == '.' || c == '?' || c == '!') {
            is_start = true;
        }
    }

    return sum;
}
