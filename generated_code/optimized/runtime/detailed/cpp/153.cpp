#include <string>
#include <vector>
using namespace std;

string Strongest_Extension(string class_name, vector<string> extensions) {
    string strongest;
    int max_strength = -1000;

    for (const string& ext : extensions) {
        int strength = 0;
        for (unsigned char c : ext) {
            strength += (c >= 'A' && c <= 'Z') - (c >= 'a' && c <= 'z');
        }
        if (strength > max_strength) {
            max_strength = strength;
            strongest = ext;
        }
    }

    return class_name + '.' + strongest;
}
