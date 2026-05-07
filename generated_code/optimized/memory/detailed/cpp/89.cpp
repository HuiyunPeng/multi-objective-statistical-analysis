#include <string>
using namespace std;

string encrypt(string s) {
    for (char &c : s) {
        c = static_cast<char>((c - 'a' + 4) % 26 + 'a');
    }
    return s;
}
