#include <string>
using namespace std;

string encrypt(string s) {
    for (char& c : s) {
        c = char((int(c) + 4 - int('a')) % 26 + int('a'));
    }
    return s;
}
