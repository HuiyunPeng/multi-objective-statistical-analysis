int get_matrix_triples(int n) {
    const long long c0 = (n + 1) / 3;   // count of i in [1..n] with (i*i - i + 1) % 3 == 0
    const long long c1 = n - c0;        // remaining values are 1 modulo 3

    const auto choose3 = [](long long x) -> long long {
        return (x >= 3) ? (x * (x - 1) * (x - 2)) / 6 : 0;
    };

    return static_cast<int>(choose3(c0) + choose3(c1));
}
