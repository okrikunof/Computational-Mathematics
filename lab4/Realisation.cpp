#include <iostream>
#include <vector>
#include "matplotlibcpp.h"
#include "ChooseApproximationFunction.h"
#include "LinearApproximation.h"
#include "QuadraticApproximation.h"

int main() {
    std::cout << "Сколько занчений x и y вы введете? (от 8 до 12)" << std::endl;
    size_t numberOfXY = 0;
    std::cin >> numberOfXY;
    if (numberOfXY > 12 || numberOfXY < 7) {
        std::cerr << "Вы ввели некорректное кол-во пар X и Y";
    }

    std::cout << "Введите значения x и y через пробел:" << std::endl;
    std::vector<double> x(numberOfXY);
    std::vector<double> y(numberOfXY);
    for (int i = 0; i < numberOfXY; i++) {
        std::cin >> x[i];
        std::cin >> y[i];
    }

//    LinearApproximation linApprox = LinearApproximation(x, y);
//    linApprox.Approximation();
    QuadraticApproximation quadraticApproximation = QuadraticApproximation(x, y);
    quadraticApproximation.Approximation();





    return 0;
}