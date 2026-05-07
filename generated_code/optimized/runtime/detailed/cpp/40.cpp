#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
#include<stdlib.h>

bool triples_sum_to_zero(vector<int> l){
    const int n = (int)l.size();
    if (n < 3) return false;

    sort(l.begin(), l.end());

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && l[i] == l[i - 1]) continue;
        if (l[i] > 0) break;
        if ((long long)l[i] + l[n - 2] + l[n - 1] < 0) continue;

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            long long sum = (long long)l[i] + l[left] + l[right];
            if (sum == 0) return true;
            if (sum < 0) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return false;
}
