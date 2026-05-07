#include <vector>
#include <unordered_map>
using namespace std;

vector<int> remove_duplicates(vector<int> numbers) {
    unordered_map<int, unsigned char> freq;
    freq.reserve(numbers.size());

    for (int x : numbers) {
        auto it = freq.find(x);
        if (it == freq.end()) {
            freq.emplace(x, 1);
        } else if (it->second < 2) {
            ++it->second;
        }
    }

    vector<int> out;
    for (int x : numbers) {
        auto it = freq.find(x);
        if (it->second == 1) {
            out.push_back(x);
        }
    }

    return out;
}
