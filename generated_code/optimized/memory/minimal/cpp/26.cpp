#include <vector>
using namespace std;

vector<int> remove_duplicates(vector<int> numbers) {
    size_t write = 0;
    for (size_t i = 0; i < numbers.size(); ++i) {
        bool duplicate = false;
        for (size_t j = 0; j < numbers.size(); ++j) {
            if (i != j && numbers[i] == numbers[j]) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            numbers[write++] = numbers[i];
        }
    }
    numbers.resize(write);
    return numbers;
}
