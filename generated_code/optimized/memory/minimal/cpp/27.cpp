#include <string>
using namespace std;

string filp_case(string str) {
    for (char &w : str) {
        if (w >= 'a' && w <= 'z') {
            w -= ('a' - 'A');
        } else if (w >= 'A' && w <= 'Z') {
            w += ('a' - 'A');
        }
    }
    return str;
}
