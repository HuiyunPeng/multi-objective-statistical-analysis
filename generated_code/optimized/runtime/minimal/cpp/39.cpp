int prime_fib(int n){
    static const int vals[] = {
        2, 3, 5, 13, 89, 233, 1597, 28657, 514229, 433494437
    };
    return (n >= 1 && n <= (int)(sizeof(vals) / sizeof(vals[0]))) ? vals[n - 1] : 0;
}
