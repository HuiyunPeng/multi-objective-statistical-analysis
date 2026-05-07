#include <vector>
using namespace std;

vector<int> sum_product(vector<int> numbers) {
    int sum = 0;
    int product = 1;

    const int* ptr = numbers.data();
    const int* end = ptr + numbers.size();

    while (ptr != end) {
        const int value = *ptr++;
        sum += value;
        product *= value;
    }

    return vector<int>{sum, product};
}
