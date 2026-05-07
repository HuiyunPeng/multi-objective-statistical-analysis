int prime_fib(int n) {
    int a = 1, b = 2, count = 0;

    while (count < n) {
        int next = a + b;
        a = b;
        b = next;

        bool isprime = false;
        if (a == 2) {
            isprime = true;
        } else if (a > 2 && (a & 1)) {
            isprime = true;
            for (int d = 3; d <= a / d; d += 2) {
                if (a % d == 0) {
                    isprime = false;
                    break;
                }
            }
        }

        if (isprime && ++count == n) {
            return a;
        }
    }

    return 0;
}
