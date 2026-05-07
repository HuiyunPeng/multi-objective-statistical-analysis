#include <string>
using namespace std;

string string_xor(string a, string b) {
    const size_t n = (a.size() < b.size()) ? a.size() : b.size();
    string output;
    output.resize(n);

    for (size_t i = 0; i < n; ++i) {
        output[i] = (a[i] == b[i]) ? '0' : '1';
    }

    return output;
}
