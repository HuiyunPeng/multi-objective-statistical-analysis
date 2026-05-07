#include <map>
#include <string>
using namespace std;

bool check_dict_case(map<string, string> dict) {
    if (dict.empty()) return false;

    for (map<string, string>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
        const string& key = it->first;
        bool hasLower = false, hasUpper = false;

        for (string::size_type i = 0; i < key.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(key[i]);

            if ((c < 'A') || (c > 'Z' && c < 'a') || (c > 'z')) return false;
            if (c >= 'A' && c <= 'Z') hasUpper = true;
            else hasLower = true;

            if (hasLower && hasUpper) return false;
        }
    }

    return true;
}
