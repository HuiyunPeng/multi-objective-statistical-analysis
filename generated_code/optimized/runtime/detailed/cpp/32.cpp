#include <vector>
#include <cmath>

using namespace std;

double poly(vector<double> xs, double x) {
    const int n = static_cast<int>(xs.size());
    if (n == 0) return 0.0;

    double sum = xs[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        sum = sum * x + xs[i];
    }
    return sum;
}

double find_zero(vector<double> xs) {
    const int n = static_cast<int>(xs.size());
    if (n == 0) return 0.0;

    double ans = 0.0;

    while (true) {
        double value = xs[n - 1];
        double driv = 0.0;

        for (int i = n - 2; i >= 0; --i) {
            driv = driv * ans + value;
            value = value * ans + xs[i];
        }

        if (fabs(value) <= 1e-6) break;
        ans -= value / driv;
    }

    return ans;
}
