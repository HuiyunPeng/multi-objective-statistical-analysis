#include <string>
#include <algorithm>

using namespace std;

string circular_shift(int x, int shift) {
    string xs = to_string(x);
    const size_t n = xs.size();

    if (shift < 0 || static_cast<size_t>(shift) > n) {
        reverse(xs.begin(), xs.end());
        return xs;
    }

    if (shift == 0 || static_cast<size_t>(shift) == n) {
        return xs;
    }

    rotate(xs.begin(), xs.end() - shift, xs.end());
    return xs;
}
