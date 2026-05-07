#include <vector>
#include <algorithm>

using namespace std;

vector<int> strange_sort_list(vector<int> lst) {
    sort(lst.begin(), lst.end());

    const size_t n = lst.size();
    const size_t lower_size = (n + 1) / 2;
    const size_t upper_size = n - lower_size;

    vector<int> upper(lst.begin() + lower_size, lst.end());

    for (size_t i = lower_size; i-- > 0;) {
        lst[2 * i] = lst[i];
    }

    for (size_t i = 0; i < upper_size; ++i) {
        lst[2 * i + 1] = upper[upper_size - 1 - i];
    }

    return lst;
}
