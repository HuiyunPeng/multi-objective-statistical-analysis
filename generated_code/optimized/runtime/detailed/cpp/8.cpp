#include <vector>
using namespace std;

vector<int> sum_product(vector<int> numbers) {
    int sum = 0;
    int product = 1;

    const int* p = numbers.data();
    const int* end = p + numbers.size();

    for (; p != end; ++p) {
        sum += *p;
        product *= *p;
    }

    return {sum, product};
}
