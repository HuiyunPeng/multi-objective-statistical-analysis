#include <vector>
#include <string>
using namespace std;

vector<string> odd_count(vector<string> lst) {
    static const char tmpl[] = "the number of odd elements in the string i of the input.";
    static const size_t tmpl_len = sizeof(tmpl) - 1;
    static const size_t i_count = 4;

    for (string& item : lst) {
        int sum = 0;
        for (char c : item) {
            if (c >= '0' && c <= '9' && ((c - '0') & 1)) {
                ++sum;
            }
        }

        string count_str = to_string(sum);
        item.clear();
        item.reserve(tmpl_len + i_count * (count_str.size() - 1));

        for (size_t i = 0; i < tmpl_len; ++i) {
            if (tmpl[i] == 'i') {
                item += count_str;
            } else {
                item += tmpl[i];
            }
        }
    }

    return lst;
}
