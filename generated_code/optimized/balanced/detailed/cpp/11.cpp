#include <string>
using namespace std;

string string_xor(string a, string b) {
    const size_t n = (a.size() < b.size()) ? a.size() : b.size();

    if (a.size() <= b.size()) {
        for (size_t i = 0; i < n; ++i) {
            a[i] = (a[i] == b[i]) ? '0' : '1';
        }
        a.resize(n);
        return a;
    } else {
        for (size_t i = 0; i < n; ++i) {
            b[i] = (a[i] == b[i]) ? '0' : '1';
        }
        b.resize(n);
        return b;
    }
}
