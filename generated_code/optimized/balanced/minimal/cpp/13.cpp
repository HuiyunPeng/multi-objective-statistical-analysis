int greatest_common_divisor(int a, int b) {
    unsigned ua = a < 0 ? static_cast<unsigned>(-(static_cast<long long>(a))) : static_cast<unsigned>(a);
    unsigned ub = b < 0 ? static_cast<unsigned>(-(static_cast<long long>(b))) : static_cast<unsigned>(b);

    while (ub != 0) {
        unsigned t = ua % ub;
        ua = ub;
        ub = t;
    }

    return static_cast<int>(ua);
}
