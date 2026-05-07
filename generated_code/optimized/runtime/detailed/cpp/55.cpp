int fib(int n){
    static int f[1000] = {0, 1};
    static int computed = 1;

    if (n <= 1) return n;

    if (n > computed) {
        for (int i = computed + 1; i <= n; ++i) {
            f[i] = f[i - 1] + f[i - 2];
        }
        computed = n;
    }

    return f[n];
}
