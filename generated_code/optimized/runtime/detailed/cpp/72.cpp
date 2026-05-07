#include <vector>
using namespace std;

bool will_it_fly(vector<int> q, int w) {
    const auto n = q.size();
    if (n == 0) return 0 <= w;

    const int* left = q.data();
    const int* right = left + n - 1;
    long long sum = 0;

    while (left < right) {
        const int a = *left++;
        const int b = *right--;
        if (a != b) return false;
        sum += static_cast<long long>(a) + b;
    }

    if (left == right) sum += *left;

    return sum <= w;
}
