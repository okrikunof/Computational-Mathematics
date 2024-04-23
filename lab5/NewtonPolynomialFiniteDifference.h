#ifndef COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALCD_H
#define COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALCD_H

double NewtonInterpolationFD(std::vector<double> &x, std::vector<double> &y, double x0) {
    std::vector<std::vector<double>> dy(x.size() - 1, std::vector<double>(x.size() - 1, 0));
    double t, h, mult, sum;
    int factorial;

    h = (x[1] - x[0]);

    for (int i = 0; i < x.size() - 1; ++i) {
        dy[i][0] = y[i + 1] - y[i];
    }

    for (int i = 1; i < x.size() - 1; ++i) {
        for (int j = 0; j < x.size() - 1 - i; ++j) {
            dy[j][i] = dy[j + 1][i - 1] - dy[j][i - 1];
        }
    }

    mult = 1;
    sum = y[0];
    t = (x0 - x[0]) / h;
    factorial = 1;
    for (int i = 0; i < x.size() - 1; ++i) {
        mult *= (t - i);
        factorial *= i + 1;
        sum += mult * dy[0][i] / (factorial);
    }

    t = (x0 - x[x.size() - 1]) / h;
    sum = y[x.size() - 1];
    mult = 1;
    factorial = 1;
    for (int i = 0; i < x.size() - 1; ++i) {
        mult *= (t + i);
        factorial *= i + 1;
        sum += mult * dy[x.size() - 1 - i - 1][i] / (factorial);
    }

    return sum;
}

#endif