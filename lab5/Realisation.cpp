#include "SolvingMethods.h"

int main() {
    std::cout << "Какой полином вы хотите использовать?\n1)Полином Лагранжа\n"
                 "2)Полином Ньютона с разделенными разностями\n3)Полином Ньютона с конечными разностями\n";

    size_t methodChoice;
    std::cin >> methodChoice;

    std::cout << "Как бы вы хотели получить данные?\n1)Ввести вручную\n"
                 "2)Считать с файла\n3)Получить из предоставленных\n";

    size_t inputChoice;
    std::cin >> inputChoice;

    if (inputChoice == 1) {
        std::cout << "Сколько значений у функции?\n";

        size_t n;
        std::cin >> n;

        std::vector<double> x_axis(n);
        std::vector<double> y_axis(n);

        std::cout << "Введите все значения x и y через пробел:\n";
        for (int i = 0; i < n; i++) {
            std::cin >> x_axis[i];
            std::cin >> y_axis[i];
        }

        std::cout << "Введите точку, в которой хотите найти значение функции: ";
        double x;
        std::cin >> x;

        double result;
        switch (methodChoice) {
            case 1:
                result = Interpolate(x_axis, y_axis, x, LagrangeInterpolation);
                break;
            case 2:
                result = Interpolate(x_axis, y_axis, x, NewtonInterpolation);
                break;
            case 3:
                result = Interpolate(x_axis, y_axis, x, interpolate);
                break;
            default:
                std::cerr << "Неверный выбор" << std::endl;
                return 1;
        }

        std::cout << "y(x) = " << result;
    }
}