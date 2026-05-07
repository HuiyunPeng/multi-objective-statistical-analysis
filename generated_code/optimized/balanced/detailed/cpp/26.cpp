#include <vector>
#include <unordered_map>
using namespace std;

vector<int> remove_duplicates(vector<int> numbers) {
    const size_t n = numbers.size();
    if (n < 2) return numbers;

    unordered_map<int, unsigned char> freq;
    freq.reserve(n);

    size_t unique_once = 0;
    for (int x : numbers) {
        auto res = freq.emplace(x, 1);
        if (res.second) {
            ++unique_once;
        } else if (res.first->second == 1) {
            res.first->second = 2;
            --unique_once;
        }
    }

    if (unique_once * 2 < n) {
        vector<int> out;
        out.reserve(unique_once);
        for (int x : numbers) {
            auto it = freq.find(x);
            if (it->second == 1) out.push_back(x);
        }
        return out;
    }

    size_t write = 0;
    for (size_t i = 0; i < n; ++i) {
        int x = numbers[i];
        auto it = freq.find(x);
        if (it->second == 1) numbers[write++] = x;
    }
    numbers.resize(write);
    return numbers;
}
