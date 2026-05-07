#include <string>
#include <vector>
using namespace std;

string Strongest_Extension(string class_name, vector<string> extensions) {
    int max_strength = -1000;
    int best_index = -1;

    for (size_t i = 0; i < extensions.size(); ++i) {
        int strength = 0;
        const string& ext = extensions[i];

        for (char c : ext) {
            if (c >= 'A' && c <= 'Z') {
                ++strength;
            } else if (c >= 'a' && c <= 'z') {
                --strength;
            }
        }

        if (strength > max_strength) {
            max_strength = strength;
            best_index = static_cast<int>(i);
        }
    }

    string result;
    result.reserve(class_name.size() + 1 + (best_index >= 0 ? extensions[best_index].size() : 0));
    result += class_name;
    result += '.';
    if (best_index >= 0) {
        result += extensions[best_index];
    }

    return result;
}
