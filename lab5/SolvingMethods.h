#ifndef COMPUTATIONAL_MATHEMATICS_SOLVINGMETHODS_H
#define COMPUTATIONAL_MATHEMATICS_SOLVINGMETHODS_H

#include <functional>
#include "LagrangePolynomial.h"
#include "NewtonPolynomialFD.h"
#include "NewtonPolynomialDD.h"

double Interpolate(std::vector<double> &x_axis, std::vector<double> &y_axis, double x,
                   std::function<double(std::vector<double> &, std::vector<double> &,
                                        double)> interpolationFunction) {
    return interpolationFunction(x_axis, y_axis, x);
}

#endif