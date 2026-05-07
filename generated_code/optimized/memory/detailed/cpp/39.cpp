int prime_fib(int n) {
    if (n <= 0) return 0;

    int a = 1, b = 2, count = 0;

    while (true) {
        b += a;
        a = b - a;

        bool isPrime = a > 1;
        if (isPrime) {
            if ((a & 1) == 0) {
                isPrime = (a == 2);
            } else {
                for (int d = 3; d <= a / d; d += 2) {
                    if (a % d == 0) {
                        isPrime = false;
                        break;
                    }
                }
            }
        }

        if (isPrime && ++count == n) {
            return a;
        }
    }
}
