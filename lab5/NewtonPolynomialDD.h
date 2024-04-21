#ifndef COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALDD_H
#define COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALDD_H

double DividedDifference(std::vector<double> &x_axis, std::vector<double> &y_axis, size_t n) {
    if (n == 0) {
        return y_axis[0];
    }
    return (y_axis[n] - y_axis[n - 1]) /
           (x_axis[n] - x_axis[n - 1]);
}

double NewtonDDInterpolation(std::vector<double> &x_axis, std::vector<double> &y_axis, double x) {
    if (x_axis.size() != y_axis.size() || x_axis.empty()) {
        throw std::invalid_argument("Неверный ввод: размеры массивов не равны или один из массивов равен нулю");
    }

    if (x < x_axis[0] || x > x_axis[x_axis.size() - 1]) {
        throw std::invalid_argument("Точка x выходит за пределы интервала x_axis");
    }

    double result = y_axis[0];
    double p = 1;
    for (size_t i = 1; i < x_axis.size(); i++) {
        p *= (x - x_axis[i - 1]);
        result += DividedDifference(x_axis, y_axis, i) * p;
    }

    return result;
}

#endif
