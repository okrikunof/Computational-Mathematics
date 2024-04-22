#ifndef COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALCD_H
#define COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALCD_H

double FiniteDifferences(const std::vector<double> &x_axis, const std::vector<double> &y_axis, int i, int j) {
    if (j == 0) {
        return y_axis[i];
    } else {
        return (FiniteDifferences(x_axis, y_axis, i, j - 1) -
                FiniteDifferences(x_axis, y_axis, i - 1, j - 1)) / (x_axis[i] - x_axis[i - j]);
    }
}

double interpolate(const std::vector<double> &x_axis, const std::vector<double> &y_axis, double y_axisx) {
    double sum = 0;
    double p = (y_axisx - x_axis[x_axis.size() / 2]) / (x_axis[1] - x_axis[0]);
    sum += y_axis[x_axis.size() / 2];

    for (int i = 1; i < x_axis.size(); ++i) {
        double term = p;
        for (int j = 1; j <= i; ++j) {
            term *= (p - j);
        }
        sum += term * FiniteDifferences(x_axis, y_axis, x_axis.size() / 2, i);
    }

    return sum;
}

#endif