#include <cstring>

int fizz_buzz(int n) {
    if (n <= 0) return 0;

    struct Precomputed {
        int next_rem[143][10];
        bool valid[143];
        Precomputed() {
            for (int r = 0; r < 143; ++r) {
                valid[r] = (r % 11 == 0 || r % 13 == 0);
                for (int d = 0; d <= 9; ++d) {
                    next_rem[r][d] = (r * 10 + d) % 143;
                }
            }
        }
    };
    static const Precomputed pre;

    auto solve_up_to = [&](int x) -> long long {
        if (x < 0) return 0;

        int digits[10];
        int len = 0;
        if (x == 0) {
            digits[len++] = 0;
        } else {
            while (x > 0) {
                digits[len++] = x % 10;
                x /= 10;
            }
        }

        long long cnt[2][143], sev[2][143];
        long long ncnt[2][143], nsev[2][143];
        std::memset(cnt, 0, sizeof(cnt));
        std::memset(sev, 0, sizeof(sev));
        cnt[1][0] = 1;

        for (int pos = len - 1; pos >= 0; --pos) {
            std::memset(ncnt, 0, sizeof(ncnt));
            std::memset(nsev, 0, sizeof(nsev));
            int limit = digits[pos];

            for (int tight = 0; tight <= 1; ++tight) {
                int max_digit = tight ? limit : 9;
                for (int rem = 0; rem < 143; ++rem) {
                    long long ways = cnt[tight][rem];
                    if (!ways) continue;
                    long long total_sev = sev[tight][rem];

                    for (int d = 0; d <= max_digit; ++d) {
                        int ntight = (tight && d == limit) ? 1 : 0;
                        int nrem = pre.next_rem[rem][d];
                        ncnt[ntight][nrem] += ways;
                        nsev[ntight][nrem] += total_sev + (d == 7 ? ways : 0);
                    }
                }
            }

            std::memcpy(cnt, ncnt, sizeof(cnt));
            std::memcpy(sev, nsev, sizeof(sev));
        }

        long long ans = 0;
        for (int rem = 0; rem < 143; ++rem) {
            if (pre.valid[rem]) {
                ans += sev[0][rem] + sev[1][rem];
            }
        }
        return ans;
    };

    return static_cast<int>(solve_up_to(n - 1));
}
