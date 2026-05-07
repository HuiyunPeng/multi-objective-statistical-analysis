int greatest_common_divisor(int a, int b) {
    unsigned ua = a < 0 ? 0u - static_cast<unsigned>(a) : static_cast<unsigned>(a);
    unsigned ub = b < 0 ? 0u - static_cast<unsigned>(b) : static_cast<unsigned>(b);

    if (ua == 0) return static_cast<int>(ub);
    if (ub == 0) return static_cast<int>(ua);

    int shift = __builtin_ctz(ua | ub);
    ua >>= __builtin_ctz(ua);

    do {
        ub >>= __builtin_ctz(ub);
        if (ua > ub) {
            unsigned t = ua;
            ua = ub;
            ub = t;
        }
        ub -= ua;
    } while (ub != 0);

    return static_cast<int>(ua << shift);
}
