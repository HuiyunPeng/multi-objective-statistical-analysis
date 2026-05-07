int digits(int n) {
    long long x = n;
    if (x < 0) x = -x;

    int prod = 1;
    bool hasOdd = false;

    do {
        int d = static_cast<int>(x % 10);
        if (d & 1) {
            prod *= d;
            hasOdd = true;
        }
        x /= 10;
    } while (x);

    return hasOdd ? prod : 0;
}
