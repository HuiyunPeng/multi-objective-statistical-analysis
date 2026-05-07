#include <stdio.h>
#include <math.h>
using namespace std;
#include <algorithm>
#include <stdlib.h>

int fibfib(int n){
    static int ff[100] = {0, 0, 1};
    static int computed = 2;

    for (int i = computed + 1; i <= n; ++i) {
        ff[i] = ff[i - 1] + ff[i - 2] + ff[i - 3];
    }
    if (n > computed) computed = n;

    return ff[n];
}
