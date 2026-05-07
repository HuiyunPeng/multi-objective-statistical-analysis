bool iscuber(int a) {
    long long x = a;
    if (x < 0) x = -x;

    int lo = 0, hi = 1290;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        long long cube = 1LL * mid * mid * mid;

        if (cube == x) return true;
        if (cube < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}
