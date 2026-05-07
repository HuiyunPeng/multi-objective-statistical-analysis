#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
#include <algorithm>
#include <stdlib.h>

bool move_one_ball(vector<int> arr) {
    const size_t n = arr.size();
    if (n < 2) return true;

    const int* a = arr.data();
    int num = 0;
    int prev = a[0];

    for (size_t i = 1; i < n; ++i) {
        const int cur = a[i];
        if (cur < prev && ++num >= 2) return false;
        prev = cur;
    }

    return num + (a[n - 1] > a[0]) < 2;
}
