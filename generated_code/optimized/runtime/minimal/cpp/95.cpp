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
            unsigned char folded = static_cast<unsigned char>(c | 32);
            if (folded < 'a' || folded > 'z') return false;

            if (c & 32)
                has_lower = true;
            else
                has_upper = true;

            if (has_lower && has_upper) return false;
        }
    }

    return true;
}
