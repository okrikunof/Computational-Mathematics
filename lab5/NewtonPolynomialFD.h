#ifndef COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALCD_H
#define COMPUTATIONAL_MATHEMATICS_NEWTONPOLYNOMIALCD_H

double FiniteDifference(double x0, double x1, double y0, double y1) {
    return (y1 - y0) / (x1 - x0);
}

double NewtonFDInterpolation(const std::vector<double> &x_axis, const std::vector<double> &y_axis, double x) {
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
        result += FiniteDifference(x_axis[i - 1], x_axis[i], y_axis[i - 1], y_axis[i]) * p;
    }
    return result;
}

#endif
