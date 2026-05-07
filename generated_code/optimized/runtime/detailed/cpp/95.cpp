#include <map>
#include <string>

using namespace std;

bool check_dict_case(map<string, string> dict) {
    if (dict.empty()) return false;

    bool has_lower = false;
    bool has_upper = false;

    for (map<string, string>::const_iterator it = dict.begin(), end = dict.end(); it != end; ++it) {
        const string& key = it->first;
        const char* p = key.data();
        const char* e = p + key.size();

        while (p != e) {
            const unsigned char c = static_cast<unsigned char>(*p++);

            if (c >= 'A' && c <= 'Z') {
                if (has_lower) return false;
                has_upper = true;
            } else if (c >= 'a' && c <= 'z') {
                if (has_upper) return false;
                has_lower = true;
            } else {
                return false;
            }
        }
    }

    return true;
}
