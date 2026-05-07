#include <vector>
#include <cmath>
using namespace std;

int sum_squares(vector<float> lst) {
    int sum = 0;
    const float* p = lst.data();
    const float* end = p + lst.size();

    for (; p != end; ++p) {
        const int c = static_cast<int>(ceilf(*p));
        sum += c * c;
    }

    return sum;
}
