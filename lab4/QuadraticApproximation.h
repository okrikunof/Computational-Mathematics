#ifndef COMPUTATIONAL_MATHEMATICS_QUADRATICAPPROXIMATION_H
#define COMPUTATIONAL_MATHEMATICS_QUADRATICAPPROXIMATION_H

#include <iostream>
#include <vector>
#include <cmath>

class QuadraticApproximation {
private:
    double n = 0;
    double S = 0, SX = 0, SX2 = 0, SY = 0, SXY = 0, SX3 = 0, SX4 = 0, SX2Y = 0;
    double a0 = 0, a1 = 0, a2 = 0;
    double epsilon = 0;
    double variance = 0;
    std::vector<double> result;
    std::vector<double> x;
    std::vector<double> y;

    std::vector<double> GaussSolve(std::vector<std::vector<double>> &a, std::vector<double> &y, int n) {
        std::vector<double> answers(n);
        int k, index;
        for (k = 0; k < n; k++) {
            double maxVal = abs(a[k][k]);
            index = k;
            for (int i = k + 1; i < n; i++) {
                if (abs(a[i][k]) > maxVal) {
                    maxVal = abs(a[i][k]);
                    index = i;
                }
            }

            // Swap individual elements in the row
            for (int j = 0; j < n; ++j)
                std::swap(a[k][j], a[index][j]);
            std::swap(y[k], y[index]);

            for (int i = k; i < n; ++i) {
                double temp = a[i][k];
                if (abs(temp) < 0.0001) continue;
                for (int j = k; j < n; j++)
                    a[i][j] = a[i][j] / temp;
                y[i] = y[i] / temp;
                if (i == k) continue;
                for (int j = 0; j < n; j++)
                    a[i][j] = a[i][j] - a[k][j];
                y[i] = y[i] - y[k];
            }
        }

        for (k = n - 1; k >= 0; k--) {
            answers[k] = y[k];
            for (int i = 0; i < k; i++)
                y[i] = y[i] - a[i][k] * answers[k];
        }
        return answers;
    }

    void SetVariance(double var) {
        variance = var;
    }

public:
    QuadraticApproximation(const std::vector<double> &x_arguments, const std::vector<double> &y_arguments) {
        if (x_arguments.size() != y_arguments.size()) {
            std::cerr << "Vectors must have the same length";
            return;
        }

        x = x_arguments;
        y = y_arguments;
        n = x.size();
    }

    void Approximation() {
        if (n == 0) {
            std::cerr << "Empty vectors";
            return;
        }

        result.resize(n);

        for (int i = 0; i < n; i++) {
            SX += x[i];
            SX2 += x[i] * x[i];
            SY += y[i];
            SXY += x[i] * y[i];
            SX3 += x[i] * x[i] * x[i];
            SX4 += x[i] * x[i] * x[i] * x[i];
            SX2Y += x[i] * x[i] * y[i];
        }

        std::vector<std::vector<double>> sum{{n,   SX,  SX2},
                                             {SX,  SX2, SX3},
                                             {SX2, SX3, SX4}};
        std::vector<double> rightSide{SY, SXY, SX2Y};

        std::vector<double> coefficients = GaussSolve(sum, rightSide, 3);
        a0 = coefficients[0];
        a1 = coefficients[1];
        a2 = coefficients[2];

        std::cout << "Result of quadratic approximation:" << std::endl;
        for (int i = 0; i < n; i++) {
            result[i] = a2 * x[i] * x[i] + a1 * x[i] + a0;
            std::cout << "P" << i + 1 << "(x) = " << a2 << " * x^2 + " << a1 << " * x + " << a0 << " -> " << result[i]
                      << std::endl;
            epsilon = (a2 * x[i] * x[i] + a1 * x[i] + a0) - y[i];
            std::cout << "ε" << i + 1 << " = " << epsilon << std::endl;
            S += epsilon * epsilon;
        }

        std::cout << "➤ S = " << S << std::endl;

        variance = sqrt(S / n);
        SetVariance(variance);
    }

    double GetVariance() {
        return variance;
    }
};

#endif
