#include <map>
#include <string>

using namespace std;

bool check_dict_case(map<string, string> dict) {
    if (dict.empty()) return false;

    bool has_lower = false, has_upper = false;

    for (const auto& entry : dict) {
        const string& key = entry.first;
        for (char c : key) {
            if (c >= 'A' && c <= 'Z') {
                has_upper = true;
            } else if (c >= 'a' && c <= 'z') {
                has_lower = true;
            } else {
                return false;
            }

            if (has_lower && has_upper) return false;
        }
    }

    return true;
}
