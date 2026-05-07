#include <vector>

static inline bool isPrime(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if ((x & 1) == 0 || x % 3 == 0) return false;
    for (int i = 5; 1LL * i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

int skjkasdkd(std::vector<int> lst) {
    int largestPrime = 0;
    for (int x : lst) {
        if (x > largestPrime && isPrime(x)) {
            largestPrime = x;
        }
    }

    int sum = 0;
    while (largestPrime > 0) {
        sum += largestPrime % 10;
        largestPrime /= 10;
    }
    return sum;
}
