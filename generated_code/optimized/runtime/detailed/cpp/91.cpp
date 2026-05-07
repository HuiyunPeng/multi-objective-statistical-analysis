#include <string>
using namespace std;

int is_bored(string S) {
    bool isstart = true;
    bool isi = false;
    int sum = 0;

    for (char c : S) {
        if (isi && c == ' ') ++sum;
        isi = (isstart && c == 'I');

        if (c != ' ') {
            isstart = (c == '.' || c == '?' || c == '!');
        }
    }

    return sum;
}
