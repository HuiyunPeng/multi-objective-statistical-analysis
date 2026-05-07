#include <string>
#include <vector>
#include <limits>

using namespace std;

string Strongest_Extension(string class_name, vector<string> extensions) {
    const string* best = nullptr;
    int best_strength = numeric_limits<int>::min();

    for (const string& ext : extensions) {
        int strength = 0;
        for (unsigned char c : ext) {
            if ((unsigned)(c - 'A') <= ('Z' - 'A')) {
                ++strength;
            } else if ((unsigned)(c - 'a') <= ('z' - 'a')) {
                --strength;
            }
        }
        if (strength > best_strength) {
            best_strength = strength;
            best = &ext;
        }
    }

    string result;
    result.reserve(class_name.size() + 1 + (best ? best->size() : 0));
    result = class_name;
    result.push_back('.');
    if (best) result += *best;
    return result;
}
