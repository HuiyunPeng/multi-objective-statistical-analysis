#include <vector>
#include <cmath>

using namespace std;

static inline double eval_poly(const vector<double>& xs, double x) {
    if (xs.empty()) return 0.0;
    double result = xs.back();
    for (int i = static_cast<int>(xs.size()) - 2; i >= 0; --i) {
        result = result * x + xs[i];
    }
    return result;
}

double poly(vector<double> xs, double x) {
    return eval_poly(xs, x);
}

double find_zero(vector<double> xs) {
    constexpr double EPS = 1e-6;
    double ans = 0.0;

    if (xs.empty()) return ans;

    while (true) {
        const int n = static_cast<int>(xs.size());
        double value = xs[n - 1];
        double deriv = 0.0;

        for (int i = n - 2; i >= 0; --i) {
            deriv = deriv * ans + value;
            value = value * ans + xs[i];
        }

        if (std::fabs(value) <= EPS) break;
        if (deriv == 0.0) break;

        ans -= value / deriv;
    }

    return ans;
}
