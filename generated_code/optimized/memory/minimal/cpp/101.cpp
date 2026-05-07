#include <vector>
#include <string>
using namespace std;

vector<string> words_string(string s) {
    vector<string> out;
    string current;

    for (char c : s) {
        if (c == ' ' || c == ',') {
            if (!current.empty()) {
                out.emplace_back(std::move(current));
                current.clear();
            }
        } else {
            current.push_back(c);
        }
    }

    if (!current.empty()) {
        out.emplace_back(std::move(current));
    }

    return out;
}
