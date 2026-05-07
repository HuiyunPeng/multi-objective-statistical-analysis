#include <vector>
using namespace std;

vector<int> intersperse(vector<int> numbers, int delimeter) {
    const size_t n = numbers.size();
    if (n <= 1) return numbers;

    vector<int> out(2 * n - 1);
    out[0] = numbers[0];

    for (size_t i = 1; i < n; ++i) {
        out[2 * i - 1] = delimeter;
        out[2 * i] = numbers[i];
    }

    return out;
}
