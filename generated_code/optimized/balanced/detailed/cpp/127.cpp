#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string intersection(vector<int> interval1, vector<int> interval2) {
    const int left = max(interval1[0], interval2[0]);
    const int right = min(interval1[1], interval2[1]);
    const long long len = (long long)right - left;

    if (len < 2) return "NO";
    if (len == 2 || len == 3) return "YES";
    if ((len & 1LL) == 0 || len % 3 == 0) return "NO";

    for (long long i = 5; i <= len / i; i += 6) {
        if (len % i == 0 || len % (i + 2) == 0) return "NO";
    }
    return "YES";
}
