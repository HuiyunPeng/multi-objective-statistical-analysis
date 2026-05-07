int multiply(int a, int b) {
    int x = a % 10;
    if (x < 0) x = -x;

    int y = b % 10;
    if (y < 0) y = -y;

    return x * y;
}
