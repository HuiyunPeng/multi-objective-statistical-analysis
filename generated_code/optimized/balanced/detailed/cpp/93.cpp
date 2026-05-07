#include <string>
using std::string;

string encode(string message) {
    for (char& c : message) {
        unsigned char uc = static_cast<unsigned char>(c);

        if (uc >= 'a' && uc <= 'z') {
            c = static_cast<char>(uc - ('a' - 'A'));
        } else if (uc >= 'A' && uc <= 'Z') {
            c = static_cast<char>(uc + ('a' - 'A'));
        }

        switch (c) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                c = static_cast<char>(c + 2);
                break;
        }
    }
    return message;
}
