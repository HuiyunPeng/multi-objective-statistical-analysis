#include <string>
#include <vector>
using namespace std;

string Strongest_Extension(string class_name, vector<string> extensions) {
    int max_strength = -1000;
    size_t best_index = 0;
    bool has_best = false;

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
            best_index = i;
            has_best = true;
        }
    }

    const string& strongest = has_best ? extensions[best_index] : string();
    class_name.reserve(class_name.size() + 1 + strongest.size());
    class_name.push_back('.');
    class_name += strongest;
    return class_name;
}
