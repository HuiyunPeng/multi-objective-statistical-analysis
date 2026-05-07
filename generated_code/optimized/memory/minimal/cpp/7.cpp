#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<string> filter_by_substring(vector<string> strings, string substring) {
    size_t write = 0;
    for (size_t read = 0; read < strings.size(); ++read) {
        if (strings[read].find(substring) != string::npos) {
            if (write != read) {
                strings[write] = std::move(strings[read]);
            }
            ++write;
        }
    }
    strings.resize(write);
    return strings;
}
