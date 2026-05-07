#include <cstring>

int fizz_buzz(int n) {
    if (n <= 0) return 0;

    unsigned int limit = static_cast<unsigned int>(n - 1);
    int digits[10];
    int len = 0;
    do {
        digits[len++] = static_cast<int>(limit % 10u);
        limit /= 10u;
    } while (limit != 0);

    int trans[143][10];
    bool valid[143];
    for (int r = 0; r < 143; ++r) {
        valid[r] = (r % 11 == 0) || (r % 13 == 0);
        for (int d = 0; d < 10; ++d) {
            trans[r][d] = (r * 10 + d) % 143;
        }
    }

    struct State {
        long long ways;
        long long sevens;
    };

    State cur[2][143][2];
    State nxt[2][143][2];
    std::memset(cur, 0, sizeof(cur));
    cur[1][0][0].ways = 1;

    for (int pos = len - 1; pos >= 0; --pos) {
        std::memset(nxt, 0, sizeof(nxt));
        const int limitDigit = digits[pos];

        for (int tight = 0; tight <= 1; ++tight) {
            const int maxDigit = tight ? limitDigit : 9;

            for (int rem = 0; rem < 143; ++rem) {
                for (int started = 0; started <= 1; ++started) {
                    const long long ways = cur[tight][rem][started].ways;
                    if (!ways) continue;

                    const long long sevens = cur[tight][rem][started].sevens;

                    for (int d = 0; d <= maxDigit; ++d) {
                        const int nextTight = tight && (d == maxDigit);

                        if (!started && d == 0) {
                            nxt[nextTight][0][0].ways += ways;
                            nxt[nextTight][0][0].sevens += sevens;
                        } else {
                            const int nextRem = started ? trans[rem][d] : d;
                            State& dst = nxt[nextTight][nextRem][1];
                            dst.ways += ways;
                            dst.sevens += sevens + (d == 7 ? ways : 0);
                        }
                    }
                }
            }
        }

        std::memcpy(cur, nxt, sizeof(cur));
    }

    long long result = 0;
    for (int tight = 0; tight <= 1; ++tight) {
        for (int rem = 0; rem < 143; ++rem) {
            if (valid[rem]) {
                result += cur[tight][rem][0].sevens;
                result += cur[tight][rem][1].sevens;
            }
        }
    }

    return static_cast<int>(result);
}
