#include <string>
#include <vector>
using namespace std;

string concatenate(vector<string> strings) {
    size_t total = 0;
    for (const string& s : strings) {
        total += s.size();
    }

    string out;
    out.reserve(total);
    for (const string& s : strings) {
        out += s;
    }
    return out;
}
