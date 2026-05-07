#include <vector>
using namespace std;

vector<int> rolling_max(vector<int> numbers) {
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < numbers[i - 1]) {
            numbers[i] = numbers[i - 1];
        }
    }
    return numbers;
}
