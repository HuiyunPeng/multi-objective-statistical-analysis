#include <vector>
using namespace std;

vector<int> sum_product(vector<int> numbers) {
    int sum = 0;
    int product = 1;

    const int* ptr = numbers.data();
    const int* end = ptr + numbers.size();
    while (ptr != end) {
        sum += *ptr;
        product *= *ptr;
        ++ptr;
    }

    return {sum, product};
}
