#include <vector>
using namespace std;

vector<int> rolling_max(vector<int> numbers) {
    const size_t n = numbers.size();
    for (size_t i = 1; i < n; ++i) {
        if (numbers[i] < numbers[i - 1]) {
            numbers[i] = numbers[i - 1];
        }
    }
    return numbers;
}
