bool iscuber(int a) {
    long long x = a;
    if (x < 0) x = -x;

    long long cube = 0;
    long long diff = 1;
    long long ddiff = 6;

    while (cube < x) {
        cube += diff;
        diff += ddiff;
        ddiff += 6;
    }

    return cube == x;
}
