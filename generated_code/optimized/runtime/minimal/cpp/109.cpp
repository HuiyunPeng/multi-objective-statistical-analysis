#include <vector>
using namespace std;

bool move_one_ball(vector<int> arr) {
    const int n = static_cast<int>(arr.size());
    if (n == 0) return true;

    int descents = 0;
    const int* a = arr.data();

    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i - 1] && ++descents >= 2) return false;
    }

    return descents == 0 || a[n - 1] <= a[0];
}
