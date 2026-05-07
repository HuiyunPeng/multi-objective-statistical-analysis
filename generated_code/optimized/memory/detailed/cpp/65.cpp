#include <string>
#include <algorithm>

using namespace std;

string circular_shift(int x, int shift) {
    string xs = to_string(x);
    const size_t len = xs.size();

    if (shift < 0 || len < static_cast<size_t>(shift)) {
        reverse(xs.begin(), xs.end());
        return xs;
    }

    rotate(xs.begin(), xs.begin() + (len - static_cast<size_t>(shift)), xs.end());
    return xs;
}
