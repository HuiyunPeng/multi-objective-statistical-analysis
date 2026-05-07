#include <string>

using std::string;

int digitSum(string s) {
    int sum = 0;
    const char* p = s.data();
    const char* end = p + s.size();

    while (p != end) {
        unsigned char c = static_cast<unsigned char>(*p++);
        if (c >= 'A' && c <= 'Z') {
            sum += c;
        }
    }

    return sum;
}
