#include <vector>
using namespace std;

vector<int> remove_duplicates(vector<int> numbers) {
    const size_t n = numbers.size();
    vector<bool> duplicated(n, false);

    for (size_t i = 0; i < n; ++i) {
        if (duplicated[i]) continue;
        for (size_t j = i + 1; j < n; ++j) {
            if (numbers[i] == numbers[j]) {
                duplicated[i] = true;
                duplicated[j] = true;
            }
        }
    }

    size_t write = 0;
    for (size_t i = 0; i < n; ++i) {
        if (!duplicated[i]) {
            numbers[write++] = numbers[i];
        }
    }
    numbers.resize(write);
    return numbers;
}
