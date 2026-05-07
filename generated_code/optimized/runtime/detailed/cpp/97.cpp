int multiply(int a, int b) {
    int da = a % 10;
    if (da < 0) da = -da;

    int db = b % 10;
    if (db < 0) db = -db;

    return da * db;
}
