#include <vector>
using std::vector;

vector<int> count_up_to(int n) {
    vector<int> out;
    if (n <= 2) return out;

    out.push_back(2);
    for (int i = 3; i < n; i += 2) {
        bool is_prime = true;
        for (size_t j = 0; j < out.size() && out[j] <= i / out[j]; ++j) {
            if (i % out[j] == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) out.push_back(i);
    }
    return out;
}
