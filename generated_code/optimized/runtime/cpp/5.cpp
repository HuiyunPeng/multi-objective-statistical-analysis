#include <stdio.h>
#include <vector>
using namespace std;

vector<int> intersperse(vector<int> numbers, int delimeter) {
    const size_t n = numbers.size();
    if (n == 0) return {};
    
    vector<int> out(2 * n - 1);
    out[0] = numbers[0];
    for (size_t i = 1, j = 1; i < n; ++i) {
        out[j++] = delimeter;
        out[j++] = numbers[i];
    }
    return out;
}
