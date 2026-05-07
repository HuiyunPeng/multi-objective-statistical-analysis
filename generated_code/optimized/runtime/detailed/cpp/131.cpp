int digits(int n){
    int prod = 1;
    bool has = false;

    unsigned int x;
    if (n < 0) {
        prod = -3;   // '-' in to_string(n) is treated as odd in the original code
        has = true;
        x = static_cast<unsigned int>(-(long long)n);
    } else {
        x = static_cast<unsigned int>(n);
    }

    if (x == 0) return has ? prod : 0;

    while (x) {
        int d = x % 10;
        if (d & 1) {
            has = true;
            prod *= d;
        }
        x /= 10;
    }

    return has ? prod : 0;
}
