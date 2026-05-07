#include <vector>
#include <cmath>

using namespace std;

double poly(vector<double> xs, double x) {
    const int n = static_cast<int>(xs.size());
    double sum = 0.0;
    for (int i = n - 1; i >= 0; --i) {
        sum = sum * x + xs[i];
    }
    return sum;
}

double find_zero(vector<double> xs) {
    double ans = 0.0;
    double value = 0.0;

    if (!xs.empty()) {
        for (int i = static_cast<int>(xs.size()) - 1; i >= 0; --i) {
            value = value * ans + xs[i];
        }
    }

    while (std::fabs(value) > 1e-6) {
        double deriv = 0.0;
        value = 0.0;

        for (int i = static_cast<int>(xs.size()) - 1; i >= 0; --i) {
            deriv = deriv * ans + value;
            value = value * ans + xs[i];
        }

        ans -= value / deriv;

        value = 0.0;
        for (int i = static_cast<int>(xs.size()) - 1; i >= 0; --i) {
            value = value * ans + xs[i];
        }
    }

    return ans;
}
