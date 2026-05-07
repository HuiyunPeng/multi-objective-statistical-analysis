#include <vector>
using namespace std;

vector<int> rolling_max(vector<int> numbers) {
    if (numbers.empty()) return numbers;

    int current_max = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < current_max) {
            numbers[i] = current_max;
        } else {
            current_max = numbers[i];
        }
    }
    return numbers;
}
