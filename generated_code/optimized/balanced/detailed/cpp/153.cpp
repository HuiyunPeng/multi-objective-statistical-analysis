#include <string>
#include <vector>
#include <limits>

using namespace std;

string Strongest_Extension(string class_name, vector<string> extensions) {
    int best_strength = numeric_limits<int>::min();
    size_t best_index = 0;
    bool found = false;

    for (size_t i = 0, n = extensions.size(); i < n; ++i) {
        const string& ext = extensions[i];
        int strength = 0;

        for (char c : ext) {
            if (c >= 'A' && c <= 'Z') {
                ++strength;
            } else if (c >= 'a' && c <= 'z') {
                --strength;
            }
        }

        if (!found || strength > best_strength) {
            best_strength = strength;
            best_index = i;
            found = true;
        }
    }

    const string& strongest = found ? extensions[best_index] : string();
    string result;
    result.reserve(class_name.size() + 1 + strongest.size());
    result += class_name;
    result.push_back('.');
    result += strongest;
    return result;
}
