#include "Calculator.hpp"

int main() {
    Calculator<double> calculator;
    std::cout << std::setprecision(5);

    std::string expression;
    std::cout << "Enter a function: ";
    std::getline(std::cin, expression);
    Calculator<double>::Tokens rpn = calculator.convertToRPN(expression);
    calculator.printRPN(rpn);

    while (true) {
        double start, end;
        std::cout << "Enter the range of integration: ";
        std::cin >> start >> end;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        const int NumSteps = 1000;
        double result = calculator.calculateIntegral(rpn, start, end, NumSteps);
        std::cout << "The integral is: " << result << std::endl;
    }

    return 0;
}
