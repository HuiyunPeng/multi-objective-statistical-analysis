#include <vector>
using namespace std;

vector<int> rolling_max(vector<int> numbers){
    if (numbers.empty()) return numbers;
    int mx = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] > mx) mx = numbers[i];
        numbers[i] = mx;
    }
    return numbers;
}
