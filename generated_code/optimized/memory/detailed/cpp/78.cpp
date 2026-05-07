#include <string>

int hex_key(std::string num) {
    int out = 0;
    for (char c : num) {
        switch (c) {
            case '2':
            case '3':
            case '5':
            case '7':
            case 'B':
            case 'D':
                ++out;
                break;
        }
    }
    return out;
}
