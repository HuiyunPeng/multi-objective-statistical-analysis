#include <string>
#include <vector>
#include <climits>
using namespace std;

string Strongest_Extension(string class_name, vector<string> extensions) {
    int best_index = -1;
    int max_strength = INT_MIN;

    const int n = static_cast<int>(extensions.size());
    for (int i = 0; i < n; ++i) {
        const string& ext = extensions[i];
        int strength = 0;

        for (char c : ext) {
            strength += (c >= 'A' && c <= 'Z') - (c >= 'a' && c <= 'z');
        }

        if (strength > max_strength) {
            max_strength = strength;
            best_index = i;
        }
    }

    string result;
    const string& strongest = (best_index >= 0) ? extensions[best_index] : string();
    result.reserve(class_name.size() + 1 + strongest.size());
    result += class_name;
    result.push_back('.');
    result += strongest;
    return result;
}
