#include <string>
#include <algorithm>

using namespace std;

string circular_shift(int x, int shift) {
    string xs = to_string(x);
    if (shift < 0 || xs.size() < static_cast<size_t>(shift)) {
        reverse(xs.begin(), xs.end());
        return xs;
    }
    if (shift == 0 || xs.empty()) return xs;
    rotate(xs.begin(), xs.end() - shift, xs.end());
    return xs;
}
