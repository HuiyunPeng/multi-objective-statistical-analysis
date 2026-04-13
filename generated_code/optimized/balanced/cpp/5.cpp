#include <vector>
using namespace std;

vector<int> intersperse(vector<int> numbers, int delimeter) {
    const size_t n = numbers.size();
    if (n < 2) return numbers;

    numbers.resize(n * 2 - 1);
    for (size_t i = n - 1; i > 0; --i) {
        numbers[i * 2] = numbers[i];
        numbers[i * 2 - 1] = delimeter;
    }
    return numbers;
}
