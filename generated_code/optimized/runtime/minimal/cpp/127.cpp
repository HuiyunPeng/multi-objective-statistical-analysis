#include <vector>
#include <string>
using namespace std;

static inline bool isPrime(long long n) {
    if (n < 2) return false;
    if (n <= 3) return true;
    if ((n & 1) == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

string intersection(vector<int> interval1, vector<int> interval2) {
    long long inter1 = interval1[0] > interval2[0] ? interval1[0] : interval2[0];
    long long inter2 = interval1[1] < interval2[1] ? interval1[1] : interval2[1];
    long long l = inter2 - inter1;
    return isPrime(l) ? "YES" : "NO";
}
