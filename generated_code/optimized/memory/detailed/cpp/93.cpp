#include <string>
using namespace std;

string encode(string message) {
    for (char& w : message) {
        if (w >= 'a' && w <= 'z') {
            w -= 32;
        } else if (w >= 'A' && w <= 'Z') {
            w += 32;
        }

        switch (w) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                w += 2;
                break;
        }
    }
    return message;
}
