#include <string>
#include <cstring>

static long long count_sevens_upto(long long limit, int mod) {
    if (limit < 0) return 0;

    const std::string s = std::to_string(limit);
    int next_rem[143][10];
    for (int r = 0; r < mod; ++r) {
        for (int d = 0; d < 10; ++d) {
            next_rem[r][d] = (r * 10 + d) % mod;
        }
    }

    long long cnt[2][143] = {};
    long long sev[2][143] = {};
    cnt[1][0] = 1;

    for (char ch : s) {
        const int up = ch - '0';
        long long ncnt[2][143] = {};
        long long nsev[2][143] = {};

        for (int tight = 0; tight <= 1; ++tight) {
            const int max_digit = tight ? up : 9;
            for (int rem = 0; rem < mod; ++rem) {
                const long long ways = cnt[tight][rem];
                if (!ways) continue;
                const long long total_sev = sev[tight][rem];

                for (int d = 0; d <= max_digit; ++d) {
                    const int ntight = tight && (d == up);
                    const int nrem = next_rem[rem][d];
                    ncnt[ntight][nrem] += ways;
                    nsev[ntight][nrem] += total_sev + (d == 7 ? ways : 0);
                }
            }
        }

        std::memcpy(cnt, ncnt, sizeof(cnt));
        std::memcpy(sev, nsev, sizeof(sev));
    }

    return sev[0][0] + sev[1][0];
}

int fizz_buzz(int n) {
    if (n <= 0) return 0;

    const long long limit = (long long)n - 1;
    const long long ans =
        count_sevens_upto(limit, 11) +
        count_sevens_upto(limit, 13) -
        count_sevens_upto(limit, 143);

    return (int)ans;
}
