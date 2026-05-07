#include <vector>
#include <unordered_map>
using namespace std;

vector<int> remove_duplicates(vector<int> numbers) {
    unordered_map<int, int> freq;
    freq.reserve(numbers.size() * 2);

    for (int x : numbers) {
        ++freq[x];
    }

    vector<int> out;
    out.reserve(numbers.size());

    for (int x : numbers) {
        if (freq[x] == 1) {
            out.push_back(x);
        }
    }

    return out;
}
