#include <string>
using std::string;

int digitSum(string s) {
    int sum = 0;
    for (char c : s) {
        if (c >= 'A' && c <= 'Z') {
            sum += static_cast<unsigned char>(c);
        }
    }
    return sum;
}
