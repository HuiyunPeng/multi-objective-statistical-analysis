#include <vector>
#include <string>
using namespace std;

string longest(vector<string> strings) {
    const string* best = nullptr;
    for (const string& s : strings) {
        if (!best || s.size() > best->size()) {
            best = &s;
        }
    }
    return best ? *best : string();
}
