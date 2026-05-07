int get_matrix_triples(int n) {
    if (n < 3) return 0;

    const long long cnt0 = (static_cast<long long>(n) + 1) / 3; // i % 3 == 2
    const long long cnt1 = static_cast<long long>(n) - cnt0;    // all others

    auto choose3 = [](long long x) -> long long {
        return (x < 3) ? 0LL : (x * (x - 1) * (x - 2)) / 6;
    };

    return static_cast<int>(choose3(cnt0) + choose3(cnt1));
}
