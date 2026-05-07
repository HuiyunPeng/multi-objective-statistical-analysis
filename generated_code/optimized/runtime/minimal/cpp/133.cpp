#include <vector>
#include <cmath>
using namespace std;

int sum_squares(vector<float> lst) {
    int sum = 0;
    const float* data = lst.data();
    const size_t n = lst.size();

    for (size_t i = 0; i < n; ++i) {
        const int c = static_cast<int>(std::ceil(data[i]));
        sum += c * c;
    }

    return sum;
}
