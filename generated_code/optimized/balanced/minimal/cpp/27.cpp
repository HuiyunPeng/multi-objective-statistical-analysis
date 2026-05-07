#include <string>
using namespace std;

string filp_case(string str) {
    for (char& c : str) {
        if (c >= 'a' && c <= 'z') {
            c -= 'a' - 'A';
        } else if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
    }
    return str;
}
