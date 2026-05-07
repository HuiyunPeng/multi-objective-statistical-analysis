#include <map>
#include <string>

using namespace std;

bool check_dict_case(map<string, string> dict) {
    if (dict.empty()) return false;

    bool has_lower = false;
    bool has_upper = false;

    for (const auto& entry : dict) {
        const string& key = entry.first;
        for (unsigned char c : key) {
            if (static_cast<unsigned>(c - 'A') <= ('Z' - 'A')) {
                has_upper = true;
            } else if (static_cast<unsigned>(c - 'a') <= ('z' - 'a')) {
                has_lower = true;
            } else {
                return false;
            }

            if (has_lower && has_upper) return false;
        }
    }

    return true;
}
