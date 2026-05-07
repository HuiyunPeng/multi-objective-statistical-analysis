#include <string>
using namespace std;

string filp_case(string str) {
    for (char &w : str) {
        if (w >= 'a' && w <= 'z') {
            w -= 32;
        } else if (w >= 'A' && w <= 'Z') {
            w += 32;
        }
    }
    return str;
}
