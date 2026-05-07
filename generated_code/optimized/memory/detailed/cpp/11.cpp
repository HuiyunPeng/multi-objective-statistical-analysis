#include <string>
using namespace std;

string string_xor(string a, string b) {
    if (a.size() <= b.size()) {
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = (a[i] == b[i]) ? '0' : '1';
        }
        return a;
    } else {
        for (size_t i = 0; i < b.size(); ++i) {
            b[i] = (a[i] == b[i]) ? '0' : '1';
        }
        return b;
    }
}
