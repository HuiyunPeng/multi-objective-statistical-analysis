#include <vector>
#include <cmath>
using namespace std;

double poly(vector<double> xs, double x) {
    double result = 0.0;
    for (size_t i = xs.size(); i-- > 0;) {
        result = result * x + xs[i];
    }
    return result;
}

double find_zero(vector<double> xs) {
    double ans = 0.0;
    const size_t n = xs.size();
    if (n == 0) return ans;

    for (int iter = 0; iter < 1000; ++iter) {
        double value = xs[n - 1];
        double deriv = 0.0;

        for (size_t i = n - 1; i-- > 0;) {
            deriv = deriv * ans + value;
            value = value * ans + xs[i];
        }

        if (fabs(value) <= 1e-6) break;
        if (fabs(deriv) <= 1e-12) break;

        ans -= value / deriv;
    }

    return ans;
}
