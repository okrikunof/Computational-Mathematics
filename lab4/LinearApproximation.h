#ifndef COMPUTATIONAL_MATHEMATICS_LINEARAPPROXIMATION_H
#define COMPUTATIONAL_MATHEMATICS_LINEARAPPROXIMATION_H

class LinearApproximation {
private:
    size_t n = 0;
    double S = 0, SX = 0, SXX = 0, SY = 0, SXY = 0;
    double delta = 0, delta1 = 0, delta2 = 0;
    double a = 0, b = 0;
    double epsilon = 0;
    double variance = 0;
    std::vector<double> result;
    std::vector<double> x;
    std::vector<double> y;

    void PearsonCorrelation() {
        double x_mean = 0;
        double y_mean = 0;
        for (double xi: x) {
            x_mean += xi;
        }
        for (double yi: y) {
            y_mean += yi;
        }
        x_mean /= x.size();
        y_mean /= y.size();

        double covariance = 0;
        for (int i = 0; i < x.size(); ++i) {
            covariance += (x[i] - x_mean) * (y[i] - y_mean);
        }

        double x_variance = 0.0;
        double y_variance = 0.0;
        for (double xi: x) {
            x_variance += (xi - x_mean) * (xi - x_mean);
        }
        for (double yi: y) {
            y_variance += (yi - y_mean) * (yi - y_mean);
        }

        std::cout << "➤ r = " << covariance / sqrt(x_variance * y_variance) << std::endl;
    }

    void SetVariance(double var) {
        variance = var;
    }

public:
    LinearApproximation(const std::vector<double> &x_arguments, const std::vector<double> &y_arguments) {
        if (x.size() != y.size()) {
            std::cerr << "Векторы должны иметь одинаковую длину";
        }

        x.resize(x_arguments.size());
        y.resize(y_arguments.size());

        for (int i = 0; i < x_arguments.size(); i++) {
            x[i] = x_arguments[i];
            y[i] = y_arguments[i];
        }
    }

    void Approximation() {
        n = x.size();
        result.resize(n);

        for (int i = 0; i < n; i++) {
            SX += x[i];
            SXX += x[i] * x[i];
            SY += y[i];
            SXY += x[i] * y[i];
        }

        delta = SXX * n - SX * SX;
        delta1 = SXY * n - SX * SY;
        delta2 = SXX * SY - SX * SXY;

        a = delta1 / delta;
        b = delta2 / delta;

        std::cout << "Result of linear approximation:" << std::endl;
        for (int i = 0; i < n; i++) {
            result[i] = a * x[i] + b;
            std::cout << "𝑷" << i + 1 << "(𝒙) = ах + a1 -> " << result[i] << std::endl;
            epsilon = (a * x[i] + b) - y[i];
            std::cout << "ε" << i + 1 << " = " << epsilon << std::endl;
            S += epsilon * epsilon;
        }

        PearsonCorrelation();
        std::cout << "➤ S = " << S << std::endl;

        variance = sqrt(S / n);
        SetVariance(variance);
    }

    double GetVariance() const {
        return variance;
    }
};

#endif