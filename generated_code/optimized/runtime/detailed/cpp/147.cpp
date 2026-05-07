int get_matrix_triples(int n){
    if (n < 3) return 0;

    long long count0 = (n + 1) / 3;   // i % 3 == 2
    long long count1 = n - count0;     // remaining values give residue 1

    long long triples0 = (count0 >= 3) ? count0 * (count0 - 1) * (count0 - 2) / 6 : 0;
    long long triples1 = (count1 >= 3) ? count1 * (count1 - 1) * (count1 - 2) / 6 : 0;

    return static_cast<int>(triples0 + triples1);
}
