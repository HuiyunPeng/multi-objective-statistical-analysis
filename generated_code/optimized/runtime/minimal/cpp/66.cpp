#include <string>
using namespace std;

int digitSum(string s) {
    int sum = 0;
    const char* p = s.data();
    const char* end = p + s.size();

    while (p != end) {
        unsigned char c = static_cast<unsigned char>(*p++);
        if (static_cast<unsigned>(c - 'A') <= ('Z' - 'A'))
            sum += c;
    }

    return sum;
}
