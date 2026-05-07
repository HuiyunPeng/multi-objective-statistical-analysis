#include <vector>
#include <string>
using namespace std;

vector<string> all_prefixes(string str) {
    vector<string> out;
    out.reserve(str.size());

    string current;
    current.reserve(str.size());

    for (char c : str) {
        current.push_back(c);
        out.push_back(current);
    }

    return out;
}
