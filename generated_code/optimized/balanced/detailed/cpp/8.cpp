#include <vector>
using namespace std;

vector<int> sum_product(vector<int> numbers) {
    int sum = 0;
    int product = 1;

    const int* it = numbers.data();
    const int* end = it + numbers.size();
    for (; it != end; ++it) {
        sum += *it;
        product *= *it;
    }

    return {sum, product};
}
