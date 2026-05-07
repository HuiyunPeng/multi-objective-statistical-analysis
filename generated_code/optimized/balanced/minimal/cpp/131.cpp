int digits(int n) {
    if (n == 0) return 0;

    int prod = 1;
    bool hasOdd = false;

    while (n > 0) {
        int d = n % 10;
        if (d & 1) {
            hasOdd = true;
            prod *= d;
        }
        n /= 10;
    }

    return hasOdd ? prod : 0;
}
