int get_matrix_triples(int n){
    long long zeros = (n + 1LL) / 3; // values equal to 0 when i % 3 == 2
    long long ones = n - zeros;      // all remaining values are 1

    long long ans = 0;
    if (zeros >= 3) ans += zeros * (zeros - 1) * (zeros - 2) / 6;
    if (ones >= 3) ans += ones * (ones - 1) * (ones - 2) / 6;

    return static_cast<int>(ans);
}
