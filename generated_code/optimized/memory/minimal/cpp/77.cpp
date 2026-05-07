bool iscuber(int a){
    long long x = a;
    if (x < 0) x = -x;

    int left = 0, right = 1290; // cbrt(INT_MAX) < 1291
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        long long cube = 1LL * mid * mid * mid;

        if (cube == x) return true;
        if (cube < x) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}
