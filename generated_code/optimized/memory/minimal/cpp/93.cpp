#include <string>
using namespace std;

string encode(string message) {
    for (char& w : message) {
        if (w >= 'a' && w <= 'z') {
            w = static_cast<char>(w - ('a' - 'A'));
        } else if (w >= 'A' && w <= 'Z') {
            w = static_cast<char>(w + ('a' - 'A'));
        }

        switch (w) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                w = static_cast<char>(w + 2);
                break;
        }
    }
    return message;
}
