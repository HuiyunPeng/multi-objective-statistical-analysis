int digits(int n){
    if (n == 0) return 0;

    int prod = 1;
    bool has = false;
    unsigned int x;

    if (n < 0) {
        prod = -3; // account for '-'
        has = true;
        x = static_cast<unsigned int>(-(long long)n);
    } else {
        x = static_cast<unsigned int>(n);
    }

    while (x) {
        unsigned int d = x % 10;
        if (d & 1U) {
            prod *= static_cast<int>(d);
            has = true;
        }
        x /= 10;
    }

    return has ? prod : 0;
}
