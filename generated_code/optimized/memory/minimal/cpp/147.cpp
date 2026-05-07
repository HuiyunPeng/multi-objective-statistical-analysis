int get_matrix_triples(int n){
    long long c1[3] = {0, 0, 0};
    long long c2[3] = {0, 0, 0};
    long long c3[3] = {0, 0, 0};

    for (int i = 1; i <= n; ++i) {
        int x = (i * i - i + 1) % 3;

        long long old_c2[3] = {c2[0], c2[1], c2[2]};
        long long old_c1[3] = {c1[0], c1[1], c1[2]};

        for (int r = 0; r < 3; ++r)
            c3[(r + x) % 3] += old_c2[r];

        for (int r = 0; r < 3; ++r)
            c2[(r + x) % 3] += old_c1[r];

        ++c1[x];
    }

    return (int)c3[0];
}
