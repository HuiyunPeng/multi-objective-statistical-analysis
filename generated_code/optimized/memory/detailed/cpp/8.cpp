#include <vector>

std::vector<int> sum_product(std::vector<int> numbers) {
    int sum = 0;
    int product = 1;

    const std::size_t n = numbers.size();
    for (std::size_t i = 0; i < n; ++i) {
        sum += numbers[i];
        product *= numbers[i];
    }

    if (n >= 2) {
        numbers[0] = sum;
        numbers[1] = product;
        numbers.resize(2);
        return numbers;
    }

    numbers.resize(2);
    numbers[0] = sum;
    numbers[1] = product;
    return numbers;
}
