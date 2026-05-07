int greatest_common_divisor(int a, int b){
    if (a == 0) return b < 0 ? -b : b;
    if (b == 0) return a < 0 ? -a : a;

    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}
