#include <string>
#include <algorithm>

std::string circular_shift(int x, int shift) {
    std::string xs = std::to_string(x);
    const std::size_t len = xs.size();

    if (len < static_cast<std::size_t>(shift)) {
        std::reverse(xs.begin(), xs.end());
        return xs;
    }

    std::rotate(xs.begin(), xs.end() - shift, xs.end());
    return xs;
}
