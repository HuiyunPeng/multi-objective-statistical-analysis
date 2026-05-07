#include <string>
using namespace std;

int count_upper(string s) {
    int count = 0;
    for (size_t i = 0, n = s.size(); i < n; i += 2) {
        char c = s[i];
        count += (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    }
    return count;
}
