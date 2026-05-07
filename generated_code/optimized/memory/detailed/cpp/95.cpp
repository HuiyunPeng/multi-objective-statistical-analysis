#include <map>
#include <string>

using namespace std;

bool check_dict_case(map<string, string> dict) {
    int islower = 0, isupper = 0;
    if (dict.empty()) return false;

    for (const auto& entry : dict) {
        const string& key = entry.first;
        for (char c : key) {
            if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z') return false;
            if (c >= 'A' && c <= 'Z') isupper = 1;
            if (c >= 'a' && c <= 'z') islower = 1;
            if (isupper && islower) return false;
        }
    }

    return true;
}
