#include <vector>
using namespace std;

vector<int> sum_product(vector<int> numbers) {
    int sum = 0, product = 1;
    for (int x : numbers) {
        sum += x;
        product *= x;
    }
    vector<int>().swap(numbers);
    return vector<int>{sum, product};
}
