int get_matrix_triples(int n){
    auto comb3 = [](long long x) -> long long {
        return x < 3 ? 0LL : x * (x - 1) * (x - 2) / 6;
    };

    long long count0 = (n + 1) / 3;  // i % 3 == 2
    long long count1 = n - count0;   // i % 3 == 0 or 1

    return static_cast<int>(comb3(count0) + comb3(count1));
}
