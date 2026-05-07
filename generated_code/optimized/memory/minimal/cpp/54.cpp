#include <string>
using namespace std;

bool same_chars(string s0, string s1) {
    for (char c : s0) {
        if (s1.find(c) == string::npos) {
            return false;
        }
    }
    for (char c : s1) {
        if (s0.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}
