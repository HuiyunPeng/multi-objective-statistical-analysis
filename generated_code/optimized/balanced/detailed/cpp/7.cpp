#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> filter_by_substring(vector<string> strings, string substring) {
    if (strings.empty() || substring.empty()) {
        return strings;
    }

    strings.erase(
        remove_if(strings.begin(), strings.end(),
                  [&substring](const string& s) {
                      return s.find(substring) == string::npos;
                  }),
        strings.end());

    return strings;
}
