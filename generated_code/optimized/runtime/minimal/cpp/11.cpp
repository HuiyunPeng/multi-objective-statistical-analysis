#include <string>
using namespace std;

string string_xor(string a, string b) {
    const size_t n = a.size() < b.size() ? a.size() : b.size();
    string output(n, '0');
    for (size_t i = 0; i < n; ++i) {
        output[i] = static_cast<char>('0' + (a[i] != b[i]));
    }
    return output;
}
