#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

double poly(vector<double> xs, double x) {
    double sum = 0.0;
    for (int i = (int)xs.size() - 1; i >= 0; --i) {
        sum = sum * x + xs[i];
    }
    return sum;
}

double find_zero(vector<double> xs) {
    double ans = 0.0;
    double value = 0.0;

    while (true) {
        double deriv = 0.0;
        value = 0.0;

        for (int i = (int)xs.size() - 1; i >= 0; --i) {
            deriv = deriv * ans + value;
            value = value * ans + xs[i];
        }

        if (fabs(value) <= 1e-6) {
            break;
        }

        ans -= value / deriv;
    }

    return ans;
}
